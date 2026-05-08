#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxV = 2e6, inf = 1e9;
int n, m;
vector<vector<char>> mat;

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
  queue<int> q; q.push(source); level[source] = 0;
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
  while (scanf("%d %d", &n, &m) != EOF)
  {
    sink = 2*n*m - 1, vertices = 2*n*m;
    for (int i = 0; i < vertices; i ++) graph[i].clear();

    mat.clear();
    mat.resize(n);
    for (int i = 0; i < n; i ++)
    {
      getchar();
      mat[i].resize(m + 1);
      for (int j = 0; j < m; j ++)
        scanf("%c", &mat[i][j]);
    }
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
      {
        if (mat[i][j] == '#') continue;
        addEdge(i*m + j, n*m + i*m + j, 1 + ((i == 0 && j == 0) || (i == n - 1 && j == m - 1)));
        if (i + 1 < n && mat[i + 1][j] != '#')
          addEdge(n*m + i*m + j, (i + 1)*m + j, 1);
        if (j + 1 < m && mat[i][j + 1] != '#')
          addEdge(n*m + i*m + j, i*m + j + 1, 1);
      }

    int ans = dinic();
    printf("%d\n", ans);
  }
  return(0);
}
