#include <bits/stdc++.h>
using namespace std;
const int maxVertices = 1e5;
int source, target, vertices, inf = 1e7;
int cost[maxVertices], prevVertex[maxVertices], prevEdge[maxVertices], minFlow[maxVertices];
int inqueue[maxVertices]; // needed for SPFA
int potentials[maxVertices], visited[maxVertices]; // needed for Dijkstra with Potentials
// Dijkstra with Potentials is faster then SPFA
// But can't be used if there are negative edges at the start


struct Edge { int to, back, flow, capacity, cost; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f, int c)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f, c});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0, -c});
}
void printGraph()
{
  printf("\ncost: %3d\n", cost[target]);
  for (int v = target, totalCost = 0; v != source; v = prevVertex[v])
  {
    totalCost += graph[prevVertex[v]][prevEdge[v]].cost;
    printf("%d%s", v, prevVertex[v] != source ? " <- " : " <- 0");
    if (prevVertex[v] == source) printf(" | totalCost: %d\n", totalCost);
  }
  for (int i = 0; i < vertices; i ++)
  {
    printf("%2d (pot: %2d):", i, potentials[i]); int k = 0;
    for (Edge &e: graph[i])
      printf(" (%2d, %2d, %3d)", e.to, e.flow, e.cost);
    printf("\n");
  }
}

bool SPFA()
{
  memset(inqueue, 0, sizeof(inqueue));
  for (int i = 0; i < vertices; i ++) cost[i] = minFlow[i] = inf;
  deque<int> q; q.push_back(source); cost[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop_front(); inqueue[u] = 0;
    for (int j = 0; j < graph[u].size(); j ++)
    {
      Edge &e = graph[u][j]; int newCost = cost[u] + e.cost;
      if (e.flow && newCost < cost[e.to])
      {
        if (!inqueue[e.to]) inqueue[e.to] = 1, q.push_back(e.to);
        cost[e.to] = newCost;
        minFlow[e.to] = min(minFlow[u], e.flow);
        prevVertex[e.to] = u, prevEdge[e.to] = j;
      }
    }
  }
  return(cost[target] != inf);
}

bool dijkstraWithPotentials()
{
  memset(visited, 0, sizeof(visited));
  for (int i = 0; i < vertices; i ++) cost[i] = minFlow[i] = inf;
  priority_queue<pair<int, int>> q;
  q.push({0, source}); cost[source] = 0;
  while (!q.empty())
  {
    int u = q.top().second; q.pop();
    if (visited[u]) continue;
    visited[u] = 1;
    for (int j = 0; j < graph[u].size(); j ++)
    {
      Edge &e = graph[u][j]; int newCost = cost[u] + e.cost + potentials[u] - potentials[e.to];
      if (e.flow && newCost < cost[e.to])
      {
        cost[e.to] = newCost;
        minFlow[e.to] = min(minFlow[u], e.flow);
        prevVertex[e.to] = u, prevEdge[e.to] = j;
        q.push({-cost[e.to], e.to});
      }
    }
  }
  for (int i = 0; i < vertices; i ++) potentials[i] += cost[i];
  return(cost[target] != inf);
}

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
  return(cost[target] != inf);
}

pair<int, int> minCostFlow()
{
  memset(potentials, 0, sizeof(potentials));
  int minCost = 0, totalFlow = 0;
  while (dijkstraWithPotentials())
  {
    int flow = minFlow[target];
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
  int n, m; scanf("%d %d", &n, &m); vertices = n;
  source = 0, target = n - 1;

  int u, v, f, c;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d %d %d", &u, &v, &f, &c);
    addEdge(u, v, f, c);
  }

  pair<int, int> ans = minCostFlow();
  printf("%d %d\n", ans.first, ans.second);

  return(0);
}
