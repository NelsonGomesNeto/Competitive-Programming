#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

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
// source (0) -[1s needed count]> x with 1 (1 : n*m) -[1]> unmarked (1 + 2*n*m : 3*n*m) -[1]> sink (1 + 3*n*m)
//            -[4s needed count]> x with 4 (1 + n*m : 2*n*m) -[1]/
/*
  adjency count:
    0 - 0
    1 - impossible
    2 - 1 + 4
    3 - impossible
    4 - 1 + 1 + 4 + 4
*/

const int maxN = 500; int n, m;
char s[maxN][maxN + 1];
int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++) scanf(" %s", s[i]);

    Dinic<int> dinic(1 + 3*n*m + 1, 0, 1 + 3*n*m, 1e8);

    bool can = true;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (s[i][j] == 'X')
        {
          int cnt = 0;
          for (int k = 0; k < 4; k++)
          {
            int ni = i + di[k], nj = j + dj[k];
            cnt += ni >= 0 && ni < n && nj >= 0 && nj < m && s[ni][nj] == '.';
          }
          if (cnt & 1)
            can = false;
          else
          {
            dinic.addEdge(dinic.source, 1 + i*m + j, cnt >> 1);
            dinic.addEdge(dinic.source, 1 + n*m + i*m + j, cnt >> 1);
          }
        }

    if (!can) printf("NO\n");
    else
    {
      int maxFlow = dinic.flow();
      printf("%d\n", maxFlow);
    }
  }
  return 0;
}
