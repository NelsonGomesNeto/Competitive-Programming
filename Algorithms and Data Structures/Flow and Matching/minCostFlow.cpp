#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Edge { int to, back; T flow, capacity, cost; };

template<typename T>
struct MinCostFlow
{
  int source, sink, vertices; T inf;
  vector<int> prevVertex, prevEdge;
  vector<T> cost, minFlow;
  vector<vector<Edge<T>>> graph;

  vector<bool> inqueue; // needed for SPFA
  vector<int> potentials; vector<bool> visited; // needed for Dijkstra with Potentials
  // Dijkstra with Potentials is faster then SPFA
  // But can't be used if there are negative edges at the start

  MinCostFlow() {}
  MinCostFlow(int vertices, int source, int sink, T inf) : vertices(vertices), source(source), sink(sink), inf(inf)
  {
    graph.resize(vertices, vector<Edge<T>>());
    prevVertex.resize(vertices), prevEdge.resize(vertices);
    cost.resize(vertices), minFlow.resize(vertices);

    inqueue.resize(vertices);
    potentials.resize(vertices), visited.resize(vertices);
  }

  void addEdge(int u, int v, int f, T c)
  {
    graph[u].push_back({v, (int)graph[v].size(), f, f, c});
    graph[v].push_back({u, (int)graph[u].size() - 1, 0, 0, -c});
  }

  void shortestPathInit()
  {
    fill(cost.begin(), cost.end(), inf);
    fill(minFlow.begin(), minFlow.end(), inf);
  }

  void printGraph()
  {
    printf("\ncost: %3d\n", cost[sink]);
    for (int v = sink, totalCost = 0; v != source; v = prevVertex[v])
    {
      totalCost += graph[prevVertex[v]][prevEdge[v]].cost;
      printf("%d%s", v, prevVertex[v] != source ? " <- " : " <- 0");
      if (prevVertex[v] == source) printf(" | totalCost: %d\n", totalCost);
    }
    for (int i = 0; i < vertices; i ++)
    {
      printf("%2d (pot: %2d):", i, potentials[i]); int k = 0;
      for (auto& e: graph[i])
        printf(" (%2d, %2d, %3d)", e.to, e.flow, e.cost);
      printf("\n");
    }
  }

  bool SPFA()
  {
    fill(inqueue.begin(), inqueue.end(), 0);
    shortestPathInit();
    deque<int> q; q.push_back(source); cost[source] = 0;
    while (!q.empty())
    {
      int u = q.front(); q.pop_front(); inqueue[u] = 0;
      for (int j = 0; j < graph[u].size(); j ++)
      {
        auto& e = graph[u][j]; int newCost = cost[u] + e.cost;
        if (e.flow && newCost < cost[e.to])
        {
          if (!inqueue[e.to]) inqueue[e.to] = 1, q.push_back(e.to);
          cost[e.to] = newCost;
          minFlow[e.to] = min(minFlow[u], e.flow);
          prevVertex[e.to] = u, prevEdge[e.to] = j;
        }
      }
    }
    return cost[sink] != inf;
  }

  bool dijkstraWithPotentials()
  {
    fill(visited.begin(), visited.end(), false);
    shortestPathInit();
    priority_queue<pair<T, int>> q;
    q.push({0, source}); cost[source] = 0;
    while (!q.empty())
    {
      int u = q.top().second; q.pop();
      if (visited[u]) continue;
      visited[u] = true;
      for (int j = 0; j < graph[u].size(); j ++)
      {
        auto& e = graph[u][j]; T newCost = cost[u] + e.cost + potentials[u] - potentials[e.to];
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
    return cost[sink] != inf;
  }

  bool bellmanFord()
  {
    shortestPathInit();
    cost[source] = 0;
    for (int i = 0, done = 0; i < vertices - 1; i ++, done = 0)
    {
      for (int u = 0; u < vertices; u ++)
        for (int j = 0; j < graph[u].size(); j ++)
        {
          auto& e = graph[u][j];
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

  pair<T, T> minCostFlow()
  {
    fill(potentials.begin(), potentials.end(), 0);

    T minCost = 0, totalFlow = 0;
    while (dijkstraWithPotentials())
    {
      T flow = minFlow[sink];
      totalFlow += flow;
      for (int v = sink; v != source; v = prevVertex[v])
      {
        auto& e = graph[prevVertex[v]][prevEdge[v]];
        e.flow -= flow;
        graph[e.to][e.back].flow += flow;
        minCost += flow * e.cost;
      }
    }
    return make_pair(minCost, totalFlow);
  }
};

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  MinCostFlow<int> mcf(n, 0, n - 1, 1e7);

  int u, v, f, c;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d %d %d", &u, &v, &f, &c);
    mcf.addEdge(u, v, f, c);
  }

  pair<int, int> ans = mcf.minCostFlow();
  printf("%d %d\n", ans.first, ans.second);

  return 0;
}
