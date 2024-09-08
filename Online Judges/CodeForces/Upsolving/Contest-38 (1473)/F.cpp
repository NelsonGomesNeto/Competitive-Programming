#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3, maxX = 101; int n;
short a[maxN];
int b[maxN];
bool done[maxX];

// source (0) -[b[i]]> numbers (1 : n) -[b[i]]> sink(n + 1)
const int maxVertices = maxN + 2, inf = 4e8;
int source, sink, vertices;
int level[maxVertices], ptr[maxVertices];

struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}
bool bfs()
{
  queue<int> q;
  memset(level, -1, sizeof(level));
  level[source] = 0, q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (auto &e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return level[sink] != -1;
}
int dfs(int u = source, int flow = inf)
{
  if (u == sink || flow == 0) return flow;
  for (int &p = ptr[u]; p < graph[u].size(); p++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[u] == level[e.to] - 1)
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
  while (~scanf("%d", &n))
  {
    source = 0, sink = n + 1;
    vertices = n + 2;

    for (int i = 0; i < n; i++)
      scanf("%hd", &a[i]);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &b[i]);
      sum += max(0, b[i]);
    }

    for (int i = 0; i < vertices; i++)
      graph[i].clear();
    for (int i = 0; i < n; i++)
    {
      if (b[i] > 0)
        addEdge(source, 1 + i, b[i]);
      if (b[i] < 0)
        addEdge(1 + i, sink, -b[i]);

      memset(done, false, sizeof(done));
      for (int j = i - 1; j >= 0; j--)
        if (!done[a[j]] && a[i] % a[j] == 0)
          addEdge(1 + i, 1 + j, inf), done[a[j]] = true;
    }

    int maxFlow = dinic();
    // printf("\t%d %d\n", maxFlow, sum);
    printf("%d\n", sum - maxFlow);
  }
  return 0;
}