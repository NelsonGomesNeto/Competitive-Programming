#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const char kStartLetter = 't';

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
    std::cout << "edges:\n";
    for (const auto& [u, v] : edges) {
      std::cout << u << " " << v << "\n";
    }
    std::cout << "computers:\n";
    for (const auto& c : computers) {
      std::cout << c << "\n";
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

    std::vector<std::vector<int>> triplets;
    for (const auto& c : computers) {
      if (c[0] != kStartLetter) continue;
      const int i = ComputerIndex(c);

      for (const int j : graph[i]) {
        for (const int k : graph[i]) {
          if (k >= j) break;
          const bool j_has_k = std::ranges::binary_search(graph[j], k);
          if (!j_has_k) continue;
          auto& triplet = triplets.emplace_back();
          triplet.push_back(i), triplet.push_back(j), triplet.push_back(k);
          std::ranges::sort(triplet);
        }
      }
    }
    MakeUnique(triplets);
    std::cout << std::format("parties: {}\n", triplets.size());
    for (const auto& triplet : triplets) {
      const int a = triplet[0], b = triplet[1], c = triplet[2];
      std::cout << std::format("{},{},{}\n", computers[a], computers[b],
                               computers[c]);
    }
    std::cout << "ans: " << triplets.size() << "\n";
  }
};
Problem problem;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
