#include <bits/stdc++.h>
using namespace std;
// source (0) -> cow (1 : n) -> bull (n+1 : n+m) -> target (n+m+1)
const int maxVertices = 1e5 + 2;
int source = 0, target, level[maxVertices], ptr[maxVertices], inf = 1e9;
queue<int> q;

struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

bool bfs()
{
  memset(level, -1, sizeof(level)); level[source] = 0; q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (auto &e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}

int dfs(int u, int flow)
{
  if (u == target || !flow) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[u] + 1 == level[e.to])
    {
      int delivered = dfs(e.to, min(e.flow, flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return(delivered);
    }
  }
  return(0);
}

int dinic()
{
  int maxFlow = 0, flow;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (flow = dfs(source, inf)) maxFlow += flow;
  }
  return(maxFlow);
}

int main()
{
  int n, m, p; scanf("%d %d %d", &n, &m, &p); target = n + m + 1;
  int u, v;
  for (int i = 0; i < n; i ++) addEdge(source, i + 1, 1);
  for (int i = 0; i < m; i ++) addEdge(i + 1 + n, target, 1);
  for (int i = 0; i < p; i ++)
  {
    scanf("%d %d", &u, &v);
    addEdge(u, v + n, 1);
  }

  printf("%d\n", dinic());
  return(0);
}
