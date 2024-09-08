#include <bits/stdc++.h>
using namespace std;

template<typename Flow>
struct Edge { int to, back; Flow flow; };

template<typename Flow>
struct Dinic
{
  int source, sink, vertices; Flow inf;
  vector<int> level, ptr;
  vector<vector<Edge<Flow>>> graph;

  Dinic() { }
  Dinic(int vertices, int source, int sink, Flow inf = numeric_limits<Flow>::max()) : vertices(vertices), source(source), sink(sink), inf(inf)
  {
    graph.resize(vertices, vector<Edge<Flow>>());
    level.resize(vertices);
    ptr.resize(vertices);
  }

  void addEdge(int u, int v, Flow f)
  {
    graph[u].push_back({v, (int)graph[v].size(), f});
    graph[v].push_back({u, (int)graph[u].size() - 1, 0});
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

  Flow dfs(int u, Flow flow)
  {
    if (u == sink || flow == 0)
      return flow;

    for (int &p = ptr[u]; p < graph[u].size(); p++)
    {
      auto &e = graph[u][p];
      if (e.flow && level[u] == level[e.to] - 1)
      {
        Flow delivered = dfs(e.to, min(flow, e.flow));
        e.flow -= delivered;
        graph[e.to][e.back].flow += delivered;
        if (delivered)
          return delivered;
      }
    }
    return 0;
  }

  Flow flow()
  {
    Flow maxFlow = 0, flow;
    while (bfs())
    {
      fill(ptr.begin(), ptr.end(), 0);
      while (flow = dfs(source, inf))
        maxFlow += flow;
    }
    return maxFlow;
  }
};
Dinic<int> dinic;

const int maxVertices = 1e5; int n, m;

int main()
{
  int n, m; scanf("%d %d", &n, &m);

  dinic = Dinic<int>(n, 0, n - 1);

  int u, v, f;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d %d", &u, &v, &f);
    dinic.addEdge(u, v, f);
  }

  int maxFlow = dinic.flow();
  printf("%d\n", maxFlow);

  return(0);
}
