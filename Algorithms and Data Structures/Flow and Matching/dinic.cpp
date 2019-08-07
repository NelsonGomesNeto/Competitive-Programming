#include <bits/stdc++.h>
using namespace std;
const int maxVertices = 1e5;
int source, target, inf = 1e8, vertices;
int level[maxVertices], ptr[maxVertices];
queue<int> q;

struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

int bfs()
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
    if (e.flow && level[u] == level[e.to] - 1)
    {
      int delivered = dfs(e.to, min(flow, e.flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return(delivered); // it's better to let it catch more flow and go with full power
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
  int n, m; scanf("%d %d", &n, &m); vertices = n;
  source = 0, target = n - 1;

  int u, v, f;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d %d", &u, &v, &f);
    addEdge(u, v, f);
  }

  int maxFlow = dinic();
  printf("%d\n", maxFlow);

  return(0);
}
