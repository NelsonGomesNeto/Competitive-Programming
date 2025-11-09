#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Problem {
  std::vector<std::pair<int, int>> restrictions;
  std::vector<std::vector<int>> rev_graph;
  std::vector<std::vector<int>> updates;
  std::vector<std::vector<bool>> updates_sets;
  int n;

  bool IsSafe(const std::vector<bool>& update_set, const int s, const int t) {
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    q.push(s);
    while (!q.empty()) {
      const int u = q.front();
      q.pop();

      if (visited[u]) continue;
      visited[u] = true;

      if (u == t) return false;

      for (const int v : rev_graph[u]) {
        if (!update_set[v]) continue;
        q.push(v);
      }
    }
    return true;
  }

  void Solve() {
    n = 0;
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      std::istringstream sin(line);
      auto& [u, v] = restrictions.emplace_back();
      sin >> u;
      sin.ignore(1);
      sin >> v;
      n = std::max({n, u + 1, v + 1});
    }
    rev_graph.resize(n, {});
    for (const auto& [u, v] : restrictions) {
      DEBUG std::cout << u << "|" << v << "\n";
      rev_graph[v].push_back(u);
      // rev_graph[u].push_back(v);
    }
    DEBUG std::cout << "\n";

    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      std::istringstream sin(line);
      std::vector<int>& update = updates.emplace_back();
      std::vector<bool>& update_set = updates_sets.emplace_back();
      update_set.resize(n);

      for (int a; sin >> a; sin.ignore(1))
        update.push_back(a), update_set[a] = true;

      DEBUG {
        for (int i = 0; i < update.size(); ++i) {
          if (i) std::cout << ",";
          std::cout << update[i];
        }
        std::cout << "\n";
      }
    }

    int ans = 0;
    for (const auto& [update, update_set] :
         std::ranges::zip_view(updates, updates_sets)) {
      bool valid = true;
      for (int i = 0; valid && i < update.size(); ++i) {
        for (int j = i + 1; valid && j < update.size(); ++j) {
          valid &= IsSafe(update_set, update[i], update[j]);
        }
      }

      if (!valid) continue;

      const int mid_value = update[(int)update.size() / 2];
      ans += mid_value;
    }
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
