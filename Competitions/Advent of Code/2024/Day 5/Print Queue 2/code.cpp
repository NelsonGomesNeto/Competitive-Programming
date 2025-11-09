#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Problem {
  std::vector<std::pair<int, int>> restrictions;
  std::vector<std::vector<int>> graph, rev_graph;
  std::vector<std::vector<int>> updates;
  std::vector<std::vector<bool>> updates_sets;
  std::vector<std::vector<int>> correct_updates;
  int n;

  std::vector<int> FindSafeOrder(const std::vector<int>& update,
                                 const std::vector<bool>& update_set) {
    std::vector<int> pending_cnt(n, 0);
    std::queue<int> q;
    for (const int u : update) {
      // u is after v
      for (const int v : rev_graph[u]) {
        if (!update_set[v]) continue;
        ++pending_cnt[u];
      }
      if (pending_cnt[u]) continue;
      q.push(u);
    }

    std::vector<int> topological_order;
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      topological_order.push_back(u);

      for (const int v : graph[u]) {
        if (!update_set[v]) continue;
        if (--pending_cnt[v] > 0) continue;
        q.push(v);
      }
    }
    return topological_order;
  }

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
    graph.resize(n, {}), rev_graph.resize(n, {});
    for (const auto& [u, v] : restrictions) {
      DEBUG std::cout << u << "|" << v << "\n";
      graph[u].push_back(v);
      rev_graph[v].push_back(u);
    }
    DEBUG std::cout << "\n";

    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      std::istringstream sin(line);
      std::vector<int>& update = updates.emplace_back();
      std::vector<bool>& update_set = updates_sets.emplace_back();
      update_set.resize(n);

      for (int a; sin >> a; sin.ignore(1))
        update.push_back(a), update_set[a] = true;

      correct_updates.emplace_back(FindSafeOrder(update, update_set));

      DEBUG {
        for (int i = 0; i < update.size(); ++i) {
          if (i) std::cout << ",";
          std::cout << update[i];
        }
        std::cout << "\n";
      }
    }

    int ans = 0;
    for (const auto& [update, update_set, correct_update] :
         std::ranges::zip_view(updates, updates_sets, correct_updates)) {
      bool valid = update == correct_update;

      if (valid) continue;

      const int mid_value = correct_update[(int)correct_update.size() / 2];
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
