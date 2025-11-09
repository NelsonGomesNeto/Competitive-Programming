#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

template <class T>
void MakeUnique(std::vector<T>& a) {
  std::ranges::sort(a);
  auto [l, r] = std::ranges::unique(a);
  a.erase(l, r);
}

struct Problem {
  using computer_set = std::bitset<520>;

  std::vector<std::pair<std::string, std::string>> edges;
  std::vector<std::string> computers;
  std::vector<std::vector<int>> graph;
  int ComputerIndex(const std::string& s) {
    return std::ranges::lower_bound(computers, s) - computers.begin();
  }

  // std::string ToString(const computer_set& s) {
  //   std::ostringstream sout;
  //   for (const int a : s) {
  //     if (!sout.str().empty()) sout << ",";
  //     sout << computers[a];
  //   }
  //   return sout.str();
  // }
  std::string ToString(const std::vector<int>& s) {
    std::ostringstream sout;
    for (const int a : s) {
      if (!sout.str().empty()) sout << ",";
      sout << computers[a];
    }
    return sout.str();
  }

  bool HasAllMask(const int u, const computer_set mask) {
    int cnt = 0;
    for (const int v : graph[u]) {
      cnt += mask[v];
    }
    return mask.count() == cnt;
  }
  std::unordered_map<computer_set, computer_set> memo;
  computer_set Dfs(const int u, computer_set mask) {
    mask[u] = true;

    auto [it, inserted] = memo.try_emplace(mask);
    if (!inserted) return it->second;

    computer_set ans = mask;
    for (const int v : graph[u]) {
      if (mask[v] || !HasAllMask(v, mask)) continue;
      const auto res = Dfs(v, mask);
      if ((int)res.count() <= (int)ans.count()) continue;
      ans = res;
    }

    return it->second = ans;
  }
  void Solve() {
    for (std::string line; std::getline(std::cin, line);) {
      std::istringstream sin(line);
      std::string u, v;
      std::getline(sin, u, '-');
      sin >> v;
      edges.emplace_back(u, v);
      computers.push_back(u);
      computers.push_back(v);
    }
    MakeUnique(computers);
    std::cout << "edges: " << edges.size() << "\n";
    for (const auto& [u, v] : edges) {
      std::cout << "\t" << u << " " << v << "\n";
    }
    std::cout << "computers: " << computers.size() << "\n";
    for (const auto& c : computers) {
      std::cout << "\t" << c << "\n";
    }

    graph.clear();
    graph.resize(computers.size(), {});
    for (const auto& [u, v] : edges) {
      const int ui = ComputerIndex(u), vi = ComputerIndex(v);
      graph[ui].push_back(vi);
      graph[vi].push_back(ui);
    }
    for (auto& c : graph) {
      std::ranges::sort(c);
    }

    memo.clear();
    computer_set best = 0;
    for (int i = 0; i < computers.size(); ++i) {
      const auto res = Dfs(i, 0);
      if ((int)res.count() <= (int)best.count()) continue;
      best = res;
    }
    std::cout << std::format("biggest: {}\n", best.count());
    std::vector<std::string> party;
    for (int i = 0; i < computers.size(); ++i) {
      if (!best[i]) continue;
      party.push_back(computers[i]);
    }
    std::ranges::sort(party);
    std::ostringstream sout;
    for (const auto& c : party) {
      if (!sout.str().empty()) sout << ",";
      sout << c;
    }
    std::cout << "password: " << sout.str() << "\n";
  }
};
Problem problem;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
