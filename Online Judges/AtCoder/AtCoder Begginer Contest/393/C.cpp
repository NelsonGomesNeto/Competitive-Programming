#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::vector<std::unordered_set<int>> graph;
  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    graph.resize(n, std::unordered_set<int>{});

    int ans = 0;
    for (int i = 0; i < m; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;

      if (u == v) {
        ++ans;
        continue;
      }
      if (graph[u].count(v)) {
        ++ans;
        continue;
      }
      graph[u].insert(v);
      graph[v].insert(u);
    }

    std::cout << ans << "\n";

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
