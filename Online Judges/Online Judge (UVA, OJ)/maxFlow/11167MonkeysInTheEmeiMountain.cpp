#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100, maxTime = 50001, maxV = 100 + 50001 + 1 + 1, inf = 1e9; int n, m;
// notice that time will be shifted by one: 1 to 50001 instead of 0 to 50000
// source (0) -[v]> monkeys (1 : n) -[1]> times (n + 1 : n + 50001) -[1]> sink (n + 50001 + 1)
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
  int t = 0;
  while (scanf("%d %d", &n, &m) && n)
  {
    sink = n + maxTime + 1; vertices = sink + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();

    int required = 0;
    for (int i = 0; i < n; i ++)
    {
      int v, a, b; scanf("%d %d %d", &v, &a, &b);
      addEdge(source, 1 + i, v), required += v;
      for (int j = a; j < b; j ++) addEdge(1 + i, n + 1 + j, 1);
    }
    for (int i = 1; i <= maxTime; i ++) addEdge(n + i, sink, m);

    int maxFlow = dinic();
    printf("Case %d: %s\n", ++ t, maxFlow == required ? "Yes" : "No");
    if (maxFlow == required)
    {
      vector<pair<int, int>> monkeys[n];
      for (int i = 1; i <= n; i ++)
        for (int p = 0; p < graph[i].size(); p ++)
          if (graph[i][p].capacity && !graph[i][p].flow)
          {
            int a = graph[i][p].to - n - 1, b = graph[i][p].to - n - 1;
            while (p < graph[i].size() && graph[i][p].capacity && !graph[i][p].flow) p ++, b ++;
            p --;
            monkeys[i - 1].push_back({a, b});
          }
      for (int i = 0; i < n; i ++)
      {
        printf("%d", (int) monkeys[i].size());
        for (auto &p: monkeys[i])
          printf(" (%d,%d)", p.first, p.second);
        printf("\n");
      }
    }
  }
  return(0);
}