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
  std::vector<computer_set> graph_bitset;
  int ComputerIndex(const std::string& s) {
    return std::ranges::lower_bound(computers, s) - computers.begin();
  }

  std::string ToString(const computer_set& s) {
    std::ostringstream sout;
    for (int a = 0; a < s.size(); ++a) {
      if (!s[a]) continue;
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

  bool HasAllMask(const int u, const computer_set& mask) {
    return (graph_bitset[u] & mask) == mask;
  }
  computer_set curr_mask;
  computer_set FindBiggestParty(int i = 0) {
    if (i == computers.size()) {
      return curr_mask;
    }

    computer_set ans = FindBiggestParty(i + 1);
    if (HasAllMask(i, curr_mask)) {
      curr_mask[i] = true;
      computer_set res = FindBiggestParty(i + 1);
      curr_mask[i] = false;
      if ((int)res.count() > (int)ans.count()) {
        ans = std::move(res);
      }
    }
    return ans;
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
    graph_bitset.resize(computers.size(), {});
    for (const auto& [u, v] : edges) {
      const int ui = ComputerIndex(u), vi = ComputerIndex(v);
      graph[ui].push_back(vi);
      graph_bitset[ui][vi] = true;
      graph[vi].push_back(ui);
      graph_bitset[vi][ui] = true;
    }
    for (auto& c : graph) {
      std::ranges::sort(c);
    }

    curr_mask = 0;
    const computer_set best = FindBiggestParty();
    std::println("biggest: {}", best.count());
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
    std::println("password: {}", sout.str());
  }
};
Problem problem;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
