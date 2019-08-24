#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 30011, maxV = 2*30011 + 1; int n, m;
const int inf = 1e9;
// vertice capacity will be necessary, so: in (1-n) out (n+1-2n)
  // even though the problem explicit says that you can't use the same vertex twice
  // but it won't pass, you must allow every vertex to be visited n times :)
// source (0) -[2]> origins (1, 3) -[1]> normal graph (2*n - {2}) -[1]> target (n+2)
int source = 0, target, vertices;
int ptr[maxV], level[maxV];
struct Edge { int to, back, capacity, flow; };
vector<Edge> graph[maxV];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}
bool bfs()
{
  memset(level, -1, sizeof(level));
  queue<int> q; q.push(source), level[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (Edge &e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return level[target] != -1;
}
int dfs(int u = source, int flow = inf)
{
  if (u == target || !flow) return flow;
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[e.to] == level[u] + 1)
    {
      int delivered = dfs(e.to, min(flow, e.flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return delivered;
    }
  }
  return 0;
}

int dinic()
{
  int maxFlow = 0, flow;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (flow = dfs()) maxFlow += flow;
  }
  return maxFlow;
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d", &n, &m);
    target = n + 2, vertices = 2*n + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();

    addEdge(source, 1, 1), addEdge(source, 3, 1);
    for (int i = 0, u, v; i < m; i ++)
    {
      scanf("%d %d", &u, &v);
      addEdge(n + u, v, 1), addEdge(n + v, u, 1);
    }
    for (int i = 1; i <= n; i ++) addEdge(i, n + i, i <= 3 ? n : n);

    int maxFlow = dinic();
    printf("%s\n", maxFlow == 2 ? "YES" : "NO");
  }
  return(0);
}