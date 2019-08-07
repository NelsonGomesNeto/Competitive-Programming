#include <bits/stdc++.h>
using namespace std;

// source (0) -> cruisers (1 : m) -> banks (1+m : n+m) -> target (n+m + 1)
const int maxVertices = 1 + 20 + 20 + 1, inf = 1e7;
int source = 0, target, vertices;
int prevVertex[maxVertices], prevEdge[maxVertices], minFlow[maxVertices];
int visited[maxVertices];
double cost[maxVertices], potentials[maxVertices];
struct Edge { int to, back, flow, capacity; double cost; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f, double c)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f, c});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0, - c});
}

bool dijkstraWithPotentials()
{
  memset(visited, 0, sizeof(visited));
  for (int i = 0; i < vertices; i ++) cost[i] = minFlow[i] = inf;
  priority_queue<pair<double, int>> pq;
  cost[source] = 0; pq.push({cost[source], source});
  while (!pq.empty())
  {
    int u = pq.top().second; pq.pop();
    if (visited[u]) continue;
    visited[u] = 1;
    for (int j = 0; j < graph[u].size(); j ++)
    {
      Edge &e = graph[u][j]; double newCost = cost[u] + e.cost + potentials[u] - potentials[e.to];
      if (e.flow && newCost < cost[e.to])
      {
        cost[e.to] = newCost;
        minFlow[e.to] = min(minFlow[u], e.flow);
        prevVertex[e.to] = u, prevEdge[e.to] = j;
        pq.push({-cost[e.to], e.to});
      }
    }
  }
  for (int i = 0; i < vertices; i ++) potentials[i] += cost[i];
  return(cost[target] != inf);
}

pair<double, int> minCostFlow()
{
  for (int i = 0; i < vertices; i ++) potentials[i] = 0;
  double minCost = 0; int totalFlow = 0;
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
  int n, m;
  while (scanf("%d %d", &n, &m) && !(!n && !m))
  {
    double cruiserTimes[n][m]; int l, r;
    for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++)
    {
      // scanf("%d.%d", &l, &r);
      // cruiserTimes[i][j] = l * 10 + r;
      scanf("%lf", &cruiserTimes[i][j]); cruiserTimes[i][j] *= 100;
    }

    target = n+m + 1; vertices = target + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();
    for (int i = 0; i < m; i ++) addEdge(source, 1 + i, 1, 0);
    for (int i = 0; i < n; i ++)
    {
      for (int j = 0; j < m; j ++)
        addEdge(1 + j, 1 + m + i, 1, cruiserTimes[i][j]);
      addEdge(1 + m + i, target, 1, 0);
    }

    pair<double, int> ans = minCostFlow();
    printf("%.2lf\n", (double) ans.first / n / 100.0 + 0.00005);
  }
  return(0);
}
