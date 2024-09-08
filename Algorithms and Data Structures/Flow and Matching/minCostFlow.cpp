#include <bits/stdc++.h>
using namespace std;

template<typename Cost, typename Flow>
struct Edge { int to, back; Flow flow; Cost cost; };

template<typename Cost, typename Flow>
struct MinCostFlow
{
  int source, sink, vertices; Flow infFlow; Cost infCost;
  vector<int> prevVertex, prevEdge;
  vector<Cost> cost;
  vector<vector<Edge<Cost, Flow>>> graph;

  vector<bool> inqueue; // needed for SPFA

  vector<Cost> potentials; vector<bool> visited; // needed for Dijkstra with Potentials

  MinCostFlow() {}
  MinCostFlow(int vertices, int source, int sink, Flow infFlow = numeric_limits<Flow>::max(), Cost infCost = numeric_limits<Cost>::max())
    : vertices(vertices), source(source), sink(sink), infFlow(infFlow), infCost(infCost)
  {
    graph.resize(vertices, vector<Edge<Cost, Flow>>());
    prevVertex.resize(vertices), prevEdge.resize(vertices);
    cost.resize(vertices);

    inqueue.resize(vertices);

    potentials.resize(vertices), visited.resize(vertices);
  }
  void addEdge(int u, int v, Flow f, Cost c)
  {
    graph[u].push_back({v, (int)graph[v].size(), f, c});
    graph[v].push_back({u, (int)graph[u].size() - 1, 0, -c});
  }

  void printFlowraph()
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

  bool bellmanFord() // slow
  {
    fill(cost.begin(), cost.end(), infCost);
    cost[source] = 0;
    for (int i = 0, done = 0; i < vertices - 1; i++, done = 0)
    {
      for (int u = 0; u < vertices; u++)
      {
        if (cost[u] == infCost) continue;
        int j = 0;
        for (const auto& e: graph[u])
        {
          Cost newCost = cost[u] + e.cost;
          if (e.flow && newCost < cost[e.to])
          {
            cost[e.to] = newCost;
            prevVertex[e.to] = u, prevEdge[e.to] = j;
            done = 1;
          }
          ++j;
        }
      }
      if (!done) break;
    }
    return cost[sink] != infCost;
  }
  bool dijkstraWithPotentials() // fast
  {
    fill(visited.begin(), visited.end(), false);
    fill(cost.begin(), cost.end(), infCost);
    priority_queue<pair<Cost, int>> pq;
    pq.push({0, source}); cost[source] = 0;
    while (!pq.empty())
    {
      int u = pq.top().second; pq.pop();
      if (visited[u]) continue;
      visited[u] = true;
      int j = 0;
      for (const auto& e: graph[u])
      {
        Cost newCost = cost[u] + e.cost + potentials[u] - potentials[e.to];
        if (e.flow && newCost < cost[e.to])
        {
          cost[e.to] = newCost;
          prevVertex[e.to] = u, prevEdge[e.to] = j;
          pq.push({-cost[e.to], e.to});
        }
        ++j;
      }
    }
    if (cost[sink] == infCost)
      return false;
    for (int i = 0; i < vertices; i++)
      potentials[i] += cost[i];
    return true;
  }
  bool SPFA() // fastest
  {
    fill(inqueue.begin(), inqueue.end(), false);
    fill(cost.begin(), cost.end(), infCost);
    queue<int> q; q.push(source); cost[source] = 0;
    while (!q.empty())
    {
      int u = q.front(); q.pop(); inqueue[u] = false;
      int j = 0;
      for (const auto& e: graph[u])
      {
        Cost newCost = cost[u] + e.cost;
        if (e.flow && newCost < cost[e.to])
        {
          if (!inqueue[e.to]) inqueue[e.to] = true, q.push(e.to);
          cost[e.to] = newCost;
          prevVertex[e.to] = u, prevEdge[e.to] = j;
        }
        ++j;
      }
    }
    return cost[sink] != infCost;
  }
  pair<Cost, Flow> minCostFlow()
  {
    fill(potentials.begin(), potentials.end(), 0);
    Cost minCost = 0; Flow totalFlow = 0;
    while (bellmanFord())
    {
      Flow flow = infFlow;
      for (int v = sink; v != source; v = prevVertex[v])
      {
        auto& e = graph[prevVertex[v]][prevEdge[v]];
        flow = min(flow, e.flow);
      }
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
  MinCostFlow<int, int> mcf(n, 0, n - 1);

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
