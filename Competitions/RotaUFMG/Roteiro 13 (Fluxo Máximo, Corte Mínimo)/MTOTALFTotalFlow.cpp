#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 700, inf = 1e9; int n, vertices, source, target;
map<string, int> stringMap;
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxN];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

int ptr[maxN], level[maxN];
bool bfs()
{
  memset(level, -1, sizeof(level)); level[source] = 0;
  queue<int> q; q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (auto &e: graph[u])
      if (level[e.to] == -1 && e.flow)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}
int dfs(int u = source, int flow = inf)
{
  if (u == target || !flow) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    auto &e = graph[u][p];
    if (level[e.to] == level[u] + 1 && e.flow)
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
    while (flow = dfs()) maxFlow += flow;
  }
  return(maxFlow);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    string u, v; int c; cin >> u >> v >> c;
    if (!stringMap.count(u)) stringMap[u] = stringMap.size();
    if (!stringMap.count(v)) stringMap[v] = stringMap.size();
    addEdge(stringMap[u], stringMap[v], c);
  }
  source = stringMap["A"], target = stringMap["Z"], vertices = stringMap.size();

  int ans = dinic();
  printf("%d\n", ans);

  return(0);
}
