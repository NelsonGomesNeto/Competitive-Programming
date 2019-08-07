#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100, maxV = 1 + 2*100*100 + 1, inf = 1e9;
int n, source, target, vertices;

char table[maxN][maxN + 1];
int horizontal[maxN][maxN], vertical[maxN][maxN];
// source (0) -> horizontal (1 : n*n) -> vertical (1 + n*n : 1 + 2*n*n - 1) -> target (1 + 2*n*n)
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxV];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

int level[maxV], ptr[maxV];
bool bfs()
{
  memset(level, -1, sizeof(level));
  queue<int> q; q.push(source); level[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (auto &e: graph[u])
      if (level[e.to] == -1 && e.flow)
        level[e.to] = level[u] + 1, q.push(e.to);
  }
  return(level[target] != -1);
}
int dfs(int u = source, int flow = inf)
{
  if (u == target || !flow) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (level[e.to] == level[u] + 1 && e.flow)
    {
      int delivered = dfs(e.to, min(flow, e.flow));
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
    while (flow = dfs()) maxFlow += flow;
  }
  return(maxFlow);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    target = 1 + 2*n*n; vertices = target + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();

    for (int i = 0; i < n; i ++) scanf(" %s", table[i]);
    int hid = 1, vid = 1 + n*n;
    for (int i = 0; i < n; i ++)
    {
      for (int j = 0; j < n; j ++)
      {
        while (j < n && table[i][j] == 'X') j ++;
        while (j < n && table[i][j] == '.') horizontal[i][j ++] = hid;
        hid ++;
      }
      for (int j = 0; j < n; j ++)
      {
        while (j < n && table[j][i] == 'X') j ++;
        while (j < n && table[j][i] == '.') vertical[j ++][i] = vid;
        vid ++;
      }
    }

    for (int h = 1; h < hid; h ++) addEdge(source, h, 1);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        if (table[i][j] == '.')
          addEdge(horizontal[i][j], vertical[i][j], 1);
    for (int v = 1 + n*n; v < vid; v ++) addEdge(v, target, 1);
    int ans = dinic();
    printf("%d\n", ans);
  }
  return(0);
}