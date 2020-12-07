#include <bits/stdc++.h>
using namespace std;

int n, m, a[100], b[100], initialSoldiers, finalSoldiers, roam[100][100];

// source (0) -> a (1 : 100) -[roads]> b (101 : 200) -> target (201)
const int maxVertices = 202; int source = 0, target, vertices, inf = 1e7;
int level[maxVertices], ptr[maxVertices]; queue<int> q;
struct Edge { int to, back, capacity, flow; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

bool bfs()
{
  memset(level, -1, sizeof(level)); level[source] = 0, q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (Edge &e: graph[u])
      if (e.flow && level[e.to] == -1)
        level[e.to] = level[u] + 1, q.push(e.to);
  }
  return(level[target] != -1);
}
int dfs(int u, int flow)
{
  if (!flow || u == target) return(flow);
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
  scanf("%d %d", &n, &m); target = 1 + 2*n, vertices = 1 + 2*n + 1;
  for (int i = 0; i < n; i ++) { scanf("%d", &a[i]); initialSoldiers += a[i]; }
  for (int i = 0; i < n; i ++) { scanf("%d", &b[i]); finalSoldiers += b[i]; }
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    addEdge(1 + u, 1 + n + v, a[u]), addEdge(1 + v, 1 + n + u, a[v]);
  }
  for (int i = 0; i < n; i ++) addEdge(source, 1 + i, a[i]), addEdge(1 + n + i, target, b[i]), addEdge(1 + i, 1 + n + i, a[i]);

  int maxFlow = initialSoldiers == finalSoldiers ? dinic() : -1;
  // printf("%d %d %d\n", initialSoldiers, finalSoldiers, maxFlow);
  printf("%s\n", (finalSoldiers == maxFlow && initialSoldiers == finalSoldiers) ? "YES" : "NO");
  if (finalSoldiers == maxFlow && initialSoldiers == finalSoldiers)
  {
    for (int i = 1; i <= n; i ++)
      for (Edge &u: graph[i])
        if (u.to >= n && u.to <= 2*n)
          roam[i - 1][u.to - n - 1] = u.capacity - u.flow;
          // printf("%d %d %d %d\n", i, u.to - n, u.capacity, u.flow);
    for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) printf("%d%c", roam[i][j], j < n - 1 ? ' ' : '\n');
  }

  return(0);
}