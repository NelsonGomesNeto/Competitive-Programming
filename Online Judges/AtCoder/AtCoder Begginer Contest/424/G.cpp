#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

template <typename Cost, typename Flow>
struct Edge {
  int to, back;
  Cost cost;
  Flow flow;
};

template <typename Cost, typename Flow>
struct MinCostFlow {
  int source, sink, vertices;
  Flow inf_flow;
  Cost inf_cost;
  std::vector<int> prev_vertex, prev_edge;
  std::vector<Cost> cost;
  std::vector<std::vector<Edge<Cost, Flow>>> graph;

  std::vector<bool> inqueue;  // needed for SPFA

  std::vector<Cost> potentials;  // needed for Dijkstra with Potentials
  std::vector<bool> visited;     // needed for Dijkstra with Potentials

  MinCostFlow() {}
  MinCostFlow(int vertices, int source, int sink,
              Cost inf_cost = std::numeric_limits<Cost>::max(),
              Flow inf_flow = std::numeric_limits<Flow>::max())
      : vertices(vertices),
        source(source),
        sink(sink),
        inf_cost(inf_cost),
        inf_flow(inf_flow) {
    graph.resize(vertices, std::vector<Edge<Cost, Flow>>());
    prev_vertex.resize(vertices), prev_edge.resize(vertices);
    cost.resize(vertices);

    inqueue.resize(vertices);

    potentials.resize(vertices), visited.resize(vertices);
  }

  void AddEdge(int u, int v, Cost c, Flow f) {
    graph[u].emplace_back(v, (int)graph[v].size(), c, f);
    graph[v].emplace_back(u, (int)graph[u].size() - 1, -c, 0);
  }

  void PrintFlowGraph() {
    for (int v = sink, total_cost = 0; v != source; v = prev_vertex[v]) {
      total_cost += graph[prev_vertex[v]][prev_edge[v]].cost;
      std::cout << v << " <- ";
      if (prev_vertex[v] == source)
        std::cout << source << " | total_cost: " << total_cost << "\n";
    }
    for (int i = 0; i < vertices; ++i) {
      std::cout << i << " (pot: " << potentials[i] << "):";
      int k = 0;
      for (auto& e : graph[i])
        std::cout << " (" << e.to << e.flow << e.cost << ")";
      std::cout << "\n";
    }
  }

  bool BellmanFord()  // slow
  {
    std::fill(cost.begin(), cost.end(), inf_cost);
    cost[source] = 0;
    for (int i = 0, done = 0; i < vertices - 1; ++i, done = 0) {
      for (int u = 0; u < vertices; u++) {
        if (cost[u] == inf_cost) continue;
        int j = 0;
        for (const auto& e : graph[u]) {
          Cost new_cost = cost[u] + e.cost;
          if (e.flow && new_cost < cost[e.to]) {
            cost[e.to] = new_cost;
            prev_vertex[e.to] = u, prev_edge[e.to] = j;
            done = 1;
          }
          ++j;
        }
      }
      if (!done) break;
    }
    return cost[sink] != inf_cost;
  }
  bool DijkstraWithPotentials()  // fast
  {
    std::fill(visited.begin(), visited.end(), false);
    std::fill(cost.begin(), cost.end(), inf_cost);
    std::priority_queue<std::pair<Cost, int>> pq;
    pq.emplace(0, source);
    cost[source] = 0;
    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (visited[u]) continue;
      visited[u] = true;
      int j = 0;
      for (const auto& e : graph[u]) {
        Cost new_cost = cost[u] + e.cost + potentials[u] - potentials[e.to];
        if (e.flow && new_cost < cost[e.to]) {
          cost[e.to] = new_cost;
          prev_vertex[e.to] = u, prev_edge[e.to] = j;
          pq.emplace(-cost[e.to], e.to);
        }
        ++j;
      }
    }
    if (cost[sink] == inf_cost) return false;
    for (int i = 0; i < vertices; ++i) potentials[i] += cost[i];
    return true;
  }
  bool SPFA()  // fastest
  {
    std::fill(inqueue.begin(), inqueue.end(), false);
    std::fill(cost.begin(), cost.end(), inf_cost);
    std::queue<int> q;
    q.push(source);
    cost[source] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inqueue[u] = false;
      int j = 0;
      for (const auto& e : graph[u]) {
        Cost new_cost = cost[u] + e.cost;
        if (e.flow && new_cost < cost[e.to]) {
          if (!inqueue[e.to]) inqueue[e.to] = true, q.push(e.to);
          cost[e.to] = new_cost;
          prev_vertex[e.to] = u, prev_edge[e.to] = j;
        }
        ++j;
      }
    }
    return cost[sink] != inf_cost;
  }
  std::pair<Cost, Flow> FindMinCostFlow() {
    std::fill(potentials.begin(), potentials.end(), 0);
    Cost min_cost = 0;
    Flow total_flow = 0;
    while (DijkstraWithPotentials()) {
      Flow flow = inf_flow;
      for (int v = sink; v != source; v = prev_vertex[v]) {
        auto& e = graph[prev_vertex[v]][prev_edge[v]];
        flow = std::min(flow, e.flow);
      }
      total_flow += flow;
      for (int v = sink; v != source; v = prev_vertex[v]) {
        auto& e = graph[prev_vertex[v]][prev_edge[v]];
        e.flow -= flow;
        graph[e.to][e.back].flow += flow;
        min_cost += flow * e.cost;
      }
    }
    return std::make_pair(min_cost, total_flow);
  }
};

// 0 -[a[i]]> (1 : n) -[1]> (1 + n : n + m) -[inf]>

struct TestCase {
  int n, m;
  std::vector<int> a;
  struct Song {
    int req, score;
  };
  std::vector<Song> songs;
  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;
    songs.resize(m);
    for (auto& [req, score] : songs) std::cin >> req >> score;

    MinCostFlow<lli, int> mcf();

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
