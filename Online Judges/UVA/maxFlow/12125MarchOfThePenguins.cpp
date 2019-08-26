#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3, maxV = 2e3 + 2, inf = 1e9; int n, penguins; double d;
struct Ice { int x, y, penguins, jumps; };
Ice ices[maxN];
// We will try all possible sinks and save the ones that all penguins can meet
// Vertex capacity will be needed
// source (0) -[penguins]> in ices (1 : n) -[jumps]> out ices (n + 1 : n + n) -[all penguins]> sink (n + n + 1)
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

double dist(int i, int j)
{
  return sqrt((ices[i].x - ices[j].x)*(ices[i].x - ices[j].x) + (ices[i].y - ices[j].y)*(ices[i].y - ices[j].y));
}
bool can(int target)
{
  for (int i = 0; i < vertices; i ++) graph[i].clear();
  for (int i = 0; i < n; i ++)
  {
    addEdge(source, 1 + i, ices[i].penguins);
    addEdge(1 + i, n + 1 + i, ices[i].jumps);
    if (i == target) addEdge(1 + i, sink, penguins);
    for (int j = 0; j < n; j ++)
      if (i != j && dist(i, j) <= d)
        addEdge(n + 1 + i, 1 + j, penguins);
  }
  int maxFlow = dinic();
  return maxFlow == penguins;
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %lf", &n, &d);
    sink = 2*n + 1; vertices = sink + 1, penguins = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d %d %d %d", &ices[i].x, &ices[i].y, &ices[i].penguins, &ices[i].jumps);
      penguins += ices[i].penguins;
    }

    vector<int> ans;
    for (int i = 0; i < n; i ++)
      if (can(i))
        ans.push_back(i);
    if (ans.empty()) printf("-1\n");
    else for (int i = 0; i < ans.size(); i ++) printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
  }
  return(0);
}