#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const lli kInf = std::numeric_limits<lli>::max();

struct TestCase {
  int n, m;
  std::vector<std::vector<std::pair<int, lli>>> graph;
  std::vector<lli> ans;
  std::vector<bool> visited;

  void Dfs(const int u) {
    if (visited[u]) return;
    visited[u] = true;
    if (ans[u] == kInf) {
      ans[u] = 0;
    }
    for (const auto& [v, w] : graph[u]) {
      if (ans[v] == kInf)
        ans[v] = w + ans[u];
      else
        assert(ans[v] - ans[u] == w);
      Dfs(v);
    }
  }

  bool Solve() {
    if (!(std::cin >> n >> m)) {
      return false;
    }

    graph.resize(n), ans.resize(n, kInf);
    for (int i = 0; i < m; ++i) {
      int u, v;
      lli w;
      std::cin >> u >> v >> w;
      --u, --v;
      graph[u].emplace_back(v, w);
      graph[v].emplace_back(u, -w);
    }

    visited.resize(n, false);
    for (int start = 0; start < n; ++start) {
      Dfs(start);
    }

    for (int i = 0; i < n; ++i) {
      if (i) std::cout << " ";
      std::cout << ans[i];
    }
    std::cout << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  while (true) {
    test_case = TestCase{};
    if (!test_case.Solve()) break;
  }
  return 0;
}