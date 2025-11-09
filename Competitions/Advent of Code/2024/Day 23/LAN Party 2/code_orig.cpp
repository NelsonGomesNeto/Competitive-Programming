#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

using computer_set = std::bitset<1024>;

template <class T>
void MakeUnique(std::vector<T>& a) {
  std::ranges::sort(a);
  auto [l, r] = std::ranges::unique(a);
  a.erase(l, r);
}

struct Problem {
  std::vector<std::pair<std::string, std::string>> edges;
  std::vector<std::string> computers;
  std::vector<std::vector<int>> graph;
  int ComputerIndex(const std::string& s) {
    return std::ranges::lower_bound(computers, s) - computers.begin();
  }

  std::string ToString(const std::set<int>& s) {
    std::ostringstream sout;
    for (const int a : s) {
      if (!sout.str().empty()) sout << ",";
      sout << computers[a];
    }
    return sout.str();
  }
  std::string ToString(const std::vector<int>& s) {
    std::ostringstream sout;
    for (const int a : s) {
      if (!sout.str().empty()) sout << ",";
      sout << computers[a];
    }
    return sout.str();
  }

  bool HasAllMask(const int u, const std::set<int> mask) {
    for (const int v : mask) {
      if (std::ranges::binary_search(graph[u], v)) continue;
      return false;
    }
    return true;
  }
  std::map<std::set<int>, std::set<int>> memo;
  std::set<int> Dfs(const int u, std::set<int> mask) {
    mask.insert(u);

    auto [it, inserted] = memo.try_emplace(mask);
    if (!inserted) return it->second;

    std::set<int> ans = mask;
    for (const int v : graph[u]) {
      if (mask.count(v) || !HasAllMask(v, mask)) continue;
      const auto res = Dfs(v, mask);
      if ((int)res.size() <= (int)ans.size()) continue;
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
    std::set<int> best;
    for (int i = 0; i < computers.size(); ++i) {
      const auto res = Dfs(i, {});
      if ((int)res.size() <= (int)best.size()) continue;
      best = res;
    }
    std::cout << std::format("biggest: {}\n", best.size());
    std::vector<std::string> party;
    for (int i = 0; i < computers.size(); ++i) {
      if (!best.count(i)) continue;
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
