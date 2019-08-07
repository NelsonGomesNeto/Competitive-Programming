#include <bits/stdc++.h>
#define lli long long int
using namespace std;
const int maxVertices = 5001;
int source = 1, target, vertices, level[maxVertices], ptr[maxVertices];
lli inf = 1e18;
queue<int> q;

struct Edge { int to, back; lli flow, capacity; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, lli f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

bool bfs()
{
  memset(level, -1, sizeof(level)); level[source] = 0;
  q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (auto &e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}

lli dfs(int u, lli flow)
{
  if (u == target || !flow) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[u] + 1 == level[e.to])
    {
      lli delivered = dfs(e.to, min(e.flow, flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return(delivered); // because it's usually better to let it reach here again once with a bigger flow
    }
  }
  return(0);
}

lli dinic()
{
  lli maxFlow = 0, flow;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (flow = dfs(source, inf)) maxFlow += flow;
  }
  return(maxFlow);
}

int main()
{
  int n, m; scanf("%d %d", &n, &m); vertices = n;
  int u, v; lli f;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d %lld", &u, &v, &f); if (u == v) continue;
    addEdge(u, v, f);
    addEdge(v, u, f);
  }

  target = n;
  lli maxFlow = dinic();
  printf("%lld\n", maxFlow);
  return(0);
}
