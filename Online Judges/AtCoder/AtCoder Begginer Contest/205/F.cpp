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

const int maxN = 100, maxQ = 100, maxM = 100; int n, m, q;
struct Block
{
  int loi, loj, hii, hij;
  void read() { scanf("%d %d %d %d", &loi, &loj, &hii, &hij); loi--, hii--, loj--, hij--; }
};
Block blocks[maxN];

/*
source (0) -[1]>
rows (1 : n) -[1]>
pieces (1 + n : n + q) -[1]>
compressedPieces (1 + n + q : n + 2*q) -[1]>
cols (1 + n + 2*q : n + 2*q + m) -[1]> sink (n + 2*q + m + 1)
*/
const int maxVertices = maxN + 2*maxQ + maxM + 2;

int main()
{
  while (~scanf("%d %d %d", &n, &m, &q))
  {
    for (int i = 0; i < q; i++)
      blocks[i].read();

    Dinic<int> dinic(n + 2*q + m + 2, 0, n + 2*q + m + 1, 1e8);

    for (int i = 0; i < n; i++)
      dinic.addEdge(dinic.source, 1 + i, 1); // source -[1]> rows

    for (int qq = 0; qq < q; qq++)
    {
      dinic.addEdge(1 + n + qq, 1 + n + q + qq, 1); // pices -[1]> compressedPieces

      for (int i = blocks[qq].loi; i <= blocks[qq].hii; i++)
        dinic.addEdge(1 + i, 1 + n + qq, 1); // rows -[1]> pieces

      for (int j = blocks[qq].loj; j <= blocks[qq].hij; j++)
        dinic.addEdge(1 + n + q + qq, 1 + n + 2*q + j, 1); // compressedPieces -[1]> cols
    }

    for (int j = 0; j < m; j++)
      dinic.addEdge(1 + n + 2*q + j, dinic.sink, 1); // cols -[1]> sink

    int ans = dinic.flow();
    printf("%d\n", ans);
  }
  return 0;
}