#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
int a[maxN][maxN], choices[maxN];
ldouble loga[maxN][maxN];

const int maxV = 202, inf = 1e9;
int source, sink, vertices;
int prevVertex[maxV], prevEdge[maxV], minFlow[maxV];
ldouble cost[maxV];
struct Edge { int to, back, capacity, flow; ldouble cost; };
vector<Edge> graph[maxV];
void addEdge(int u, int v, int f, ldouble c)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f, c});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0, -c});
}
// source (0) -[]> options (1 : n) -> position (1 + n : n + n) -> sink (n + n + 1)

bool bellmanFord()
{
  for (int i = 0; i < vertices; i ++) cost[i] = minFlow[i] = inf;
  cost[source] = 0;
  for (int i = 0, done = 0; i < vertices - 1; i ++, done = 0)
  {
    for (int u = 0; u < vertices; u ++)
      for (int j = 0; j < graph[u].size(); j ++)
      {
        Edge &e = graph[u][j];
        if (e.flow && cost[u] + e.cost < cost[e.to])
        {
          cost[e.to] = cost[u] + e.cost;
          prevVertex[e.to] = u, prevEdge[e.to] = j;
          minFlow[e.to] = min(minFlow[u], e.flow);
          done = 1;
        }
      }
    if (!done) break;
  }
  return cost[sink] != inf;
}
pair<ldouble, int> minCostFlow()
{
  ldouble minCost = 0; int totalFlow = 0;
  while (bellmanFord())
  {
    int flow = minFlow[sink];
    totalFlow += flow;
    for (int v = sink; v != source; v = prevVertex[v])
    {
      Edge &e = graph[prevVertex[v]][prevEdge[v]];
      e.flow -= flow;
      graph[e.to][e.back].flow += flow;
      minCost += e.cost;
    }
  }
  return make_pair(minCost, totalFlow);
}

int main()
{
  scanf("%d", &n);
  sink = n + n + 1; vertices = n + n + 2;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      scanf("%d", &a[i][j]);
      loga[i][j] = log(a[i][j]);
    }

  for (int i = 0; i < n; i ++)
    addEdge(source, 1 + i, 1, 0);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      addEdge(1 + i, 1 + n + j, 1, -loga[i][j]);
  for (int i = 0; i < n; i ++)
    addEdge(1 + n + i, sink, 1, 0);

  pair<ldouble, int> ans = minCostFlow();
  DEBUG printf("%Lf %d\n", ans.first, ans.second);
  for (int i = 0; i < n; i ++)
    for (Edge &e: graph[1 + i])
      if (e.to >= 1 + n && e.flow == 0)
        choices[e.to - (1 + n)] = i;
  for (int i = 0; i < n; i ++)
    printf("%d%c", choices[i] + 1, i < n - 1 ? ' ' : '\n');

  return 0;
}