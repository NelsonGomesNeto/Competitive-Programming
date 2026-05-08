#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
ans[i] = number of simple paths from 1 to N and size i
THE PATH MUST BE FROM 1 TO N!!!!

Maybe we can build a tree, compute the heights for every
vertex.

Then, we can build a much smaller graph with just the extra edges and make a DFS
starting from each vertex which has an extra edge. Note that those vertices will
have a starting height based on the tree.
*/

struct TestCase {
  int n, m;
  std::vector<std::pair<int, int>> edges;
  std::vector<std::vector<int>> graph;

  std::vector<int> cnt;
  std::vector<bool> visited;
  void Naive(const int u = 0, const int depth = 0) {
    if (u == n - 1) {
      ++cnt[depth];
      return;
    }
    if (visited[u]) return;
    visited[u] = true;
    for (const int v : graph[u]) Naive(v, depth + 1);
    visited[u] = false;
  }
  void SolveNaive() {
    cnt.resize(n, 0), visited.resize(n, false);
    Naive();
    for (int i = 1; i < n; ++i) {
      if (i > 1) std::cout << " ";
      std::cout << cnt[i];
    }
    std::cout << "\n";
  }

  std::vector<int> height;
  std::vector<std::vector<int>> subgraph;
  void Solve() {
    height.resize(n, -1);
    std::set<std::pair<int, int>> used_edges;
    std::queue<std::tuple<int, int, int>> q;
    q.emplace(0, -1, 0);
    while (!q.empty()) {
      const auto [u, prv, depth] = q.front();
      q.pop();
      if (height[u] != -1) continue;
      used_edges.emplace(u, prv), used_edges.emplace(prv, u);
      height[u] = depth;
      for (const int v : graph[u]) {
        if (v == prv) continue;
        q.emplace(v, u, depth + 1);
      }
    }

    subgraph.resize(n, std::vector<int>{});
    for (const auto [u, v] : edges) {
      if (used_edges.count({u, v})) continue;
      subgraph[u].push_back(v), subgraph[v].push_back(u);
    }

    // For every vertex except N, try all paths that don't pass through N
    // That should give us all paths that u can be visited (and the distance)
    // Then, if a vertex can reach N we can use that to count
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    edges.resize(m), graph.resize(n, {});
    for (auto& [u, v] : edges) {
      std::cin >> u >> v;
      --u, --v;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    // SolveNaive();
    Solve();

    return true;
  }
};

int main() {
  while (true) {
    TestCase test_case{};
    if (!test_case.Run()) break;
  }
  return 0;
}