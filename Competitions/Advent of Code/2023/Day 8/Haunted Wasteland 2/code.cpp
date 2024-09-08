#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

std::string instructions;

std::vector<std::string> places;
int PlaceIndex(const std::string& p) {
  return std::lower_bound(places.begin(), places.end(), p) - places.begin();
}

std::vector<std::vector<std::string>> graph_str;
std::vector<std::vector<int>> graph;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::cin >> instructions;
  std::cin.ignore();

  std::string u, l, r;
  while (std::cin >> u) {
    std::cin.ignore(std::numeric_limits<int>::max(), '(');
    std::cin >> l;
    l.pop_back();
    std::cin.ignore(std::numeric_limits<int>::max(), ' ');
    std::cin >> r;
    r.pop_back();
    graph_str.push_back({u, l, r});
  }

  for (const auto& ulr : graph_str) {
    for (const auto& p : ulr) places.push_back(p);
  }
  sort(places.begin(), places.end());
  places.resize(
      std::distance(places.begin(), std::unique(places.begin(), places.end())));

  graph.resize(places.size());
  for (const auto& ulr : graph_str) {
    const int u = PlaceIndex(ulr[0]), l = PlaceIndex(ulr[1]),
              r = PlaceIndex(ulr[2]);
    graph[u].push_back(l);
    graph[u].push_back(r);
  }

  int steps = 0;
  std::vector<int> curr;
  for (int i = 0; i < places.size(); ++i) {
    if (places[i].back() == 'A') {
      curr.push_back(i);
    }
  }
  std::map<int, int> frequency;
  while (frequency.size() != curr.size()) {
    for (char op : instructions) {
      for (int& pos : curr) pos = graph[pos][op == 'R'];
      ++steps;
    }
    for (int i = 0; i < curr.size(); ++i) {
      if (places[curr[i]].back() != 'Z') continue;
      frequency.try_emplace(i, steps);
    }
  }
  DEBUG {
    std::cout << "Frequency:";
    for (const auto [i, f] : frequency) std::cout << " " << "(" << i << ", " << f << ")";
    std::cout << std::endl;
  }

  lli ans = 1;
  for (const auto [_, f] : frequency) {
    ans = std::lcm(ans, f);
  }

  std::cout << ans << std::endl;

  return 0;
}
