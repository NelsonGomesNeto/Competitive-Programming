#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, k;
int ans[maxN][maxN];

// source (0) -[1]> number (1 : n) -[1]> column (1 + n : 2 * n) -[1]> sink (1 + 2 * n)
const int maxV = (1 + 2 * maxN) + 1, inf = 1e6;
int source, sink, vertices;
int ptr[maxV], level[maxV];
struct Edge { int to, back, capacity, flow; };
vector<Edge> graph[maxV];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int)graph[v].size(), f, f});
  graph[v].push_back({u, (int)graph[u].size() - 1, 0, 0});
}
bool bfs()
{
  fill(level, level+vertices, -1);
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
  if (!flow || u == sink) return flow;
  for (int &i = ptr[u]; i < graph[u].size(); i++)
  {
    Edge &e = graph[u][i];
    if (e.flow && level[e.to] == level[u] + 1)
    {
      int delivered = dfs(e.to, min(e.flow, flow));
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
    fill(ptr, ptr+vertices, 0);
    while (flow = dfs()) maxFlow += flow;
  }
  return maxFlow;
}

void buildGraph(int i)
{
  for (int u = 0; u < vertices; u++) graph[u].clear();

  for (int num = 1; num <= n; num++)
  {
    addEdge(source, num, 1);
    if (num == ans[i][i])
      addEdge(ans[i][i], 1 + n + i, 1);
    else
      for (int j = 0; j < n; j++)
      {
        bool can = true;
        for (int ii = 0; ii < n; ii++)
          if (ans[ii][j] == num)
            can = false;
        if (can) addEdge(num, 1 + n + j, 1);
      }
  }

  for (int j = 0; j < n; j++)
    addEdge(1 + n + j, sink, 1);
}
bool valid(int a, int b, int c)
{
  memset(ans, -1, sizeof(ans));
  for (int i = 0; i < n; i++) ans[i][i] = i < n - 2 ? a : i < n - 1 ? b : c;

  for (int i = n - 1; i >= 0; i--)
  {
    buildGraph(i);
    if (dinic() != n)
      return false;
    for (int num = 1; num <= n; num++)
      for (Edge &e: graph[num])
        if (!e.flow)
          ans[i][e.to - (1 + n)] = num;
  }
  return true;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);

    source = 0, sink = (1 + 2 * n);
    vertices = sink + 1;

    bool can = false;
    for (int a = 1; a <= n && !can; a++)
      for (int b = 1; b <= n && !can; b++)
        for (int c = b; c <= n && !can; c++)
          if ((n - 2) * a + b + c == k && valid(a, b, c))
            can = true;

    printf("Case #%d: %s\n", tt, can ? "POSSIBLE" : "IMPOSSIBLE");
    if (can)
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          printf("%d%c", ans[i][j], j < n - 1 ? ' ' : '\n');
  }
  return 0;
}