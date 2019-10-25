#include <bits/stdc++.h>
using namespace std;
// source (0) -> horizontal (1 : 50*100) -> vertical (50*100+1: 50*100*2) -> target (50*100*2+1)
const int maxVertices = 1 + 50*100 + 50*100 + 1;
int source = 0, target, inf = 1e9, level[maxVertices], ptr[maxVertices];
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
  int n;
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < maxVertices; i ++) graph[i].clear();
    char board[n][n + 1]; for (int i = 0; i < n; i ++) scanf("\n%s", board[i]);
    int horizontal[n][n], vertical[n][n], hMax, vMax;
    for (int i = 0, h = 0, v = 0; i < n; i ++, h ++, v ++)
    {
      for (int j = 0; j < n; j ++)
      {
        if (board[i][j] == 'X') { if (j) h ++; while (j < n && board[i][j] == 'X') j ++; if (j == n) h --; j --; }
        else horizontal[i][j] = h;
      }
      for (int j = 0; j < n; j ++)
      {
        if (board[j][i] == 'X') { if (j) v ++; while (j < n && board[j][i] == 'X') j ++; if (j == n) v --; j --; }
        else vertical[j][i] = v;
      }
      hMax = h, vMax = v;
    }
    target = hMax + 1 + vMax + 1 + 1;

    for (int i = 0; i <= hMax; i ++) addEdge(source, i + 1, 1);
    for (int i = 0; i <= vMax; i ++) addEdge(hMax + 1 + i + 1, target, 1);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        if (board[i][j] != 'X')
          addEdge(horizontal[i][j] + 1, hMax + 1 + vertical[i][j] + 1, 1);

    printf("%d\n", dinic());
  }
  return(0);
}
