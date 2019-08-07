#include <bits/stdc++.h>
using namespace std;
#define lli long long int
// source (0) -> nodes (1, n - 2) -> target (n - 1)
const int maxVertices = 101;
lli inf = 1e18, cost[maxVertices], minFlow[maxVertices];
int source = 0, target, vertices, prevVertex[maxVertices], prevEdge[maxVertices];
struct Edge
{
  int to, back; lli flow, capacity, cost;
};
vector<Edge> graph[maxVertices];

void addEdge(int u, int v, lli f, lli c)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f, c});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0, -c});
}

int bellmanFord()
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
  return(cost[target] != inf);
}

pair<lli, lli> minCostFlow()
{
  lli minCost = 0, totalFlow = 0;
  while (bellmanFord())
  {
    lli flow = minFlow[target];
    totalFlow += flow;
    for (int v = target; v != source; v = prevVertex[v])
    {
      Edge &e = graph[prevVertex[v]][prevEdge[v]];
      e.flow -= flow;
      graph[e.to][e.back].flow += flow;
      minCost += flow * e.cost;
    }
  }
  return(make_pair(minCost, totalFlow));
}

int main()
{
  int n, m;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i <= n; i ++) graph[i].clear();
    lli edges[m][3]; for (int i = 0; i < m; i ++) scanf("%lld %lld %lld", &edges[i][0], &edges[i][1], &edges[i][2]);
    lli data, capacity; scanf("%lld %lld", &data, &capacity);

    target = n, vertices = n + 1;
    addEdge(0, 1, data, 0);
    for (int i = 0; i < m; i ++)
    {
      addEdge(edges[i][0], edges[i][1], capacity, edges[i][2]);
      addEdge(edges[i][1], edges[i][0], capacity, edges[i][2]);
    }

    pair<lli, lli> ans = minCostFlow();
    if (ans.second < data) printf("Impossible.\n");
    else printf("%lld\n", ans.first);
  }
  return(0);
}
