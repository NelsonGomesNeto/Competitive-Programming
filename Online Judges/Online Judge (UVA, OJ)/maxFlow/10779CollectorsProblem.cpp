#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 10, maxM = 25, maxV = 10 + 25 + 2, inf = 1e9; int n, m;
int stickers[maxN][maxM];
// source (0) -[Bob's amount]> stickers (1 : m) -[They don't have]> friends (m + 1 : m + n) -[They can release]> back to stickers -[1]> sink (m + n + 1)
int source = 0, sink, vertices;
int ptr[maxV], level[maxV];
struct Edge { int to, back, flow, capacity; };
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
  return level[sink] != -1;
}
int dfs(int u = source, int flow = inf)
{
  if (u == sink || !flow) return flow;
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
  for (int tt = 1; tt <= t; tt ++)
  {
    scanf("%d %d", &n, &m);
    sink = n + m + 1; vertices = sink + 1;
    memset(stickers, 0, sizeof(stickers));
    for (int i = 0; i < vertices; i ++) graph[i].clear();

    for (int i = 0, k, s; i < n; i ++)
    {
      scanf("%d", &k);
      while (k --)
      {
        scanf("%d", &s);
        stickers[i][s - 1] ++;
      }
    }

    // Bob's stickers before
    for (int i = 0; i < m; i ++) addEdge(source, 1 + i, stickers[0][i]);
    // Bob's stickers after
    for (int i = 0; i < m; i ++) addEdge(1 + i, sink, 1);
    // Friends can receive these
    for (int i = 1; i < n; i ++)
      for (int j = 0; j < m; j ++)
        if (!stickers[i][j])
          addEdge(1 + j, m + i, 1);
    // Friends can give these
    for (int i = 1; i < n; i ++)
      for (int j = 0; j < m; j ++)
        if (stickers[i][j] > 1)
          addEdge(m + i, 1 + j, stickers[i][j] - 1);

    int maxFlow = dinic();
    printf("Case #%d: %d\n", tt, maxFlow);
  }
  return(0);
}