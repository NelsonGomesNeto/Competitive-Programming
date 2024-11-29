#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kTarget = 0;

struct TestCase {
  int n, m;
  std::vector<std::vector<int>> graph;

  int Bfs() {
    std::vector<bool> visited(n, false);
    std::queue<std::pair<int, int>> q;
    q.emplace(kTarget, 0);
    while (!q.empty()) {
      const auto [u, d] = q.front();
      q.pop();
      if (d && u == kTarget) return d;
      if (visited[u]) continue;
      visited[u] = true;
      for (const int v : graph[u]) {
        q.emplace(v, d + 1);
      }
    }
    return -1;
  }

  bool Solve() {
    if (!(std::cin >> n >> m)) return false;
    graph.resize(n);
    for (int i = 0; i < m; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      graph[u].push_back(v);
    }

    const int ans = Bfs();
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  do {
    test_case = TestCase{};
  } while (test_case.Solve());
  return 0;
}
