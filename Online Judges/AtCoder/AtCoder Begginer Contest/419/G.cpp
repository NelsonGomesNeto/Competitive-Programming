#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
ans[i] = number of simple paths from 1 to N and size i

Maybe we can build a tree, compute the heights for every
vertex and then *somehow* try to introduce back the
remaining edges.
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
  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    edges.resize(m), graph.resize(n, {});
    for (auto& [u, v] : edges) {
      std::cin >> u >> v;
      --u, --v;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    cnt.resize(n, 0), visited.resize(n, false);
    Naive();
    for (int i = 1; i < n; ++i) {
      if (i > 1) std::cout << " ";
      std::cout << cnt[i];
    }
    std::cout << "\n";

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