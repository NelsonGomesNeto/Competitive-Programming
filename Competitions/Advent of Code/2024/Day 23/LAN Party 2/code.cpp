#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
Oh yes, another refreshing easy problem to rest from Day 21 and probably to
prepare for a HEAVY Day 24 (and it was hahaha).

It was still a pretty cool problem, although I chose to run a DFS instead of
just doing a recursive BruteForce on "pick" or "not-pick" a node hahaha.

Anyways, it ran on 1.3s and after optimizing to the recursive BruteForce I got
down to 0.2s \o/.
Curiously, at the same day, I also optimized the DFS to use bitset instead of
sets and it ran on 0.25s hahaha.
*/

using computer_set = std::unordered_set<int>;

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

  bool HasAllMask(const int u, const computer_set& mask) {
    for (const int v : mask) {
      if (std::ranges::binary_search(graph[u], v)) continue;
      return false;
    }
    return true;
  }
  computer_set curr_mask;
  computer_set FindBiggestParty(int i = 0) {
    if (i == computers.size()) {
      return curr_mask;
    }

    computer_set ans = FindBiggestParty(i + 1);
    if (HasAllMask(i, curr_mask)) {
      curr_mask.insert(i);
      computer_set res = FindBiggestParty(i + 1);
      curr_mask.erase(i);
      if ((int)res.size() > (int)ans.size()) {
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
    for (const auto& [u, v] : edges) {
      const int ui = ComputerIndex(u), vi = ComputerIndex(v);
      graph[ui].push_back(vi);
      graph[vi].push_back(ui);
    }
    for (auto& c : graph) {
      std::ranges::sort(c);
    }

    curr_mask.clear();
    const computer_set best = FindBiggestParty();
    std::println("biggest: {}", best.size());
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
