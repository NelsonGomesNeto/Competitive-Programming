#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::vector<int> p;
  std::vector<std::pair<int, int>> swaps;
  std::vector<std::vector<int>> graph;

  std::vector<bool> visited;
  std::pair<std::vector<int>, std::vector<int>> Bfs(const int start) {
    std::queue<int> q;
    q.push(start);
    std::vector<int> positions, values;
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      if (visited[u]) continue;
      visited[u] = true;
      positions.push_back(u), values.push_back(p[u]);
      for (const int v : graph[u]) {
        q.push(v);
      }
    }
    return {positions, values};
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    p.resize(n);
    for (auto& pi : p) std::cin >> pi;
    swaps.resize(m);
    for (auto& [a, b] : swaps) {
      std::cin >> a >> b;
      --a, --b;
    }

    std::vector<int> ans = p;
    graph.resize(n, {});
    visited.resize(n, false);
    for (const auto [a, b] : swaps) {
      if (a == b) continue;
      graph[a].push_back(b), graph[b].push_back(a);
    }
    for (const auto [i, pi] : p | std::views::enumerate) {
      if (visited[i]) continue;

      auto [positions, values] = Bfs(i);
      std::ranges::sort(positions), std::ranges::sort(values, std::greater());
      for (const auto [pos, val] : std::views::zip(positions, values)) {
        ans[pos] = val;
      }
    }

    std::println("{}", ans | std::views::transform([](const auto val) {
                         return std::format("{}", val);
                       }) | std::views::join_with(' ') |
                           std::ranges::to<std::string>());

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
