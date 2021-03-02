#include <bits/stdc++.h>
#define DEBUG if(1)
#define DEBUG2 if(1)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  We can solve this problem with maximum flow, but first we have to transform
  the problem.

  Instead of maximizing the number of different pairs, we can minimize the equal.
    c[i][j] == c[i + 1][j] (or any other direction) is what we want to avoid.
    So, we must count every equal pair.

  Let's check 4 different cases:
    1 - if c[i][j] == c[i + 1][j]:
      We lose 1 point
    2 - if c[i][j] != c[i + 1][j]:
      We lose 0 points
    3 - if c[i][j] == c[i + 2][j] and c[i + 1][j] == '?':
      We lose 0 points
    4 - if c[i][j] != c[i + 2][j] and c[i + 1][j] == '?':
      No matter the choice for c[i + 1][j], we lose 1 point.

  We can generify these cases:
    5 - if c[i][j] == c[i + k][j] and c[i + 1 : i + k - 1][j] == '?':
      We lose (k mod 2) points
        If their distance is even: lose 0 points
        If their distance is odd: lose 1 point
    6 - if c[i][j] != c[i + k][j] and c[i + 1 : i + k - 1][j] == '?':
      We lose (1 - (k mod 2)) points
        If their distance is even: lose 1 points
        If their distance is odd: lose 0 point

  Notice that we will only lose points through fixed colors since the '?' can
  be the best possible.
  But we need to find a way to count all of these losses, which is where max flow comes in.

  Let's look at 5 and 6:
    k == 1 (will lose 1 point if):
      B -> B or W -> W
    k == 2 (will lose 1 point if):
      B -> W or W -> B
    k == 3 (will lose 1 point if):
      B -> B or W -> W

    It would be very useful if we could manipulate these cases such that all
    of them where B -> W or W -> B.

    What if for (k mod 2) == 1 we flipped every B and every W (swap B and W).
    Then every loss condition would be B -> W or W -> B.
      Actually, W -> B is just B -> W with negative k.

    Notice that the same simplification could be achieved if we flipped every
    cell whose position (i, j) is ((i + j) mod 2 == 1).

    Now, if a cell with 'B' has a path that goes through a 'W', it means we
    will lose 1 point.

  So, the algorithm will be the following:
    1 - Flip every cell whose position (i, j) is ((i + j) mod 2 == 1).
    2 - Build a graph that represents our conditions
      2.1 - source -[inf capacity]> cells with 'B' (after flipping)
      2.2 - cells with 'W' (after flipping) -[inf capacity]> sink
      2.3 - cell -[1 capacity]> cell neighbors (i + 1, j), (i, j + 1), (i - 1, j), (i, j - 1)
    3 - ans = 2*n*(n - 1) - maxFlow()
      2*n*(n - 1) is the maximum possible
      maxFlow is the amount of points we will lose

  I still don't know how to color the '?' based on the maxFlow answer. If you
  know, tell me.
*/

const int maxN = 1e2; int n;
char c[maxN][maxN + 1];

// source (0) -[paint white, inf]> grid-graph (1 : n*n) -[paint black, inf]> sink (n * n + 1)
const int maxV = maxN*maxN + 2;

template<typename T>
struct Edge { int to, back; T flow, capacity; };

template<typename T>
struct Dinic
{
  int source, sink, vertices; T inf;
  vector<int> level, ptr;
  vector<vector<Edge<T>>> graph;

  Dinic() { }
  Dinic(int vertices, int source, int sink, T inf) : vertices(vertices), source(source), sink(sink), inf(inf)
  {
    graph.resize(vertices, vector<Edge<T>>());
    level.resize(vertices);
    ptr.resize(vertices);
  }

  void addEdge(int u, int v, T f)
  {
    graph[u].push_back({v, (int)graph[v].size(), f, f});
    graph[v].push_back({u, (int)graph[u].size() - 1, 0, 0});
  }

  bool bfs()
  {
    fill(level.begin(), level.end(), -1);
    level[source] = 0;
    queue<int> q; q.push(source);
    while (!q.empty())
    {
      int u = q.front(); q.pop();
      for (auto &e: graph[u])
        if (e.flow && level[e.to] == -1)
          q.push(e.to), level[e.to] = level[u] + 1;
    }
    return level[sink] != -1;
  }

  T dfs(int u, T flow)
  {
    if (u == sink || flow == 0)
      return flow;

    for (int &p = ptr[u]; p < graph[u].size(); p++)
    {
      auto &e = graph[u][p];
      if (e.flow && level[u] == level[e.to] - 1)
      {
        T delivered = dfs(e.to, min(flow, e.flow));
        e.flow -= delivered;
        graph[e.to][e.back].flow += delivered;
        if (delivered)
          return delivered;
      }
    }
    return 0;
  }

  T flow()
  {
    T maxFlow = 0, flow;
    while (bfs())
    {
      fill(ptr.begin(), ptr.end(), 0);
      while (flow = dfs(source, inf))
        maxFlow += flow;
    }
    return maxFlow;
  }
};

int di[4] = {0, 1, -1, 0}, dj[4] = {1, 0, 0, -1};

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf(" %s", c[i]);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (((i + j) & 1) && c[i][j] != '?')
          c[i][j] = c[i][j] == 'B' ? 'W' : 'B';

    Dinic<int> dinic(n*n + 2, 0, n*n + 1, 1e9);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
        if (c[i][j] == 'W')
          dinic.addEdge(dinic.source, 1 + i*n + j, 1e6);
        if (c[i][j] == 'B')
          dinic.addEdge(1 + i*n + j, dinic.sink, 1e6);

        for (int k = 0; k < 4; k++)
        {
          int ni = i + di[k], nj = j + dj[k];
          if (ni >= 0 && ni < n && nj >= 0 && nj < n)
            dinic.addEdge(1 + i*n + j, 1 + ni*n + nj, 1);
        }
      }

    int ans = 2*n*(n - 1) - dinic.flow();
    printf("%d\n", ans);

    DEBUG {
      // recovering the filling
      // I don't know how to recover the filling :/

      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          if (((i + j) & 1) && c[i][j] != '?')
            c[i][j] = c[i][j] == 'B' ? 'W' : 'B';

      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          if (c[i][j] == '?')
          {
            queue<pair<int, int>> q;
            q.push({1 + i*n + j, -1});
            while (!q.empty())
            {
              int u = q.front().first, prv = q.front().second; q.pop();
              DEBUG2 printf("\t%d (%d) %d | %d %d\n", u, dinic.sink, prv, prv / n, prv % n);
              if (u == dinic.sink)
              {
                int ni = prv / n, nj = prv % n;
                c[i][j] = !((ni + nj) & 1) ? c[ni][nj] == 'B' ? 'W' : 'B' : c[ni][nj] == 'B' ? 'W' : 'B';
                break;
              }

              for (auto &e: dinic.graph[u])
              {
                DEBUG2 printf("\t\t%d %d %d\n", e.to, e.flow, e.capacity);
                if (e.flow < e.capacity)
                {
                  q.push({e.to, u});
                }
              }
            }
          }

      char base = c[0][0];
      if (base == '?')
        base = 'W';
      char opposite = base == 'W' ? 'B' : 'W';

      // for (int i = 0; i < n; i++)
      //   for (int j = 0; j < n; j++)
      //     if (c[i][j] == '?')
      //     {
      //       int blacks = 0, whites = 0;
      //       for (int k = 0; k < 4; k++)
      //       {
      //         int ni = i + di[k], nj = j + dj[k];
      //         if (ni >= 0 && ni < n && nj >= 0 && nj < n)
      //           blacks += c[ni][nj] == 'B', whites += c[ni][nj] == 'W';
      //       }
      //       c[i][j] = blacks >= whites ? 'W' : 'B';
      //       // c[i][j] = (i + j) & 1 ? opposite : base;
      //     }

      DEBUG2
        for (int i = 0; i < n; i++)
          printf("%s\n", c[i]);

      int ans2 = 0;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          for (int k = 0; k < 4; k++)
          {
            int ni = i + di[k], nj = j + dj[k];
            if (ni >= 0 && ni < n && nj >= 0 && nj < n)
              ans2 += c[i][j] != c[ni][nj];
          }
      ans2 >>= 1;
      printf("%d\n", ans2);
      // assert(ans == ans2);
    }
  }
  return 0;
}