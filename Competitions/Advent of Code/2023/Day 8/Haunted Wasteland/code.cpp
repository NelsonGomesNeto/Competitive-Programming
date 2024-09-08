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

  int ans = 0, curr = 0;
  while (curr != places.size() - 1) {
    for (char i : instructions) {
      DEBUG {
        std::cout << "Curr: " << curr << " | " << places[curr] << std::endl;
        std::cout << std::flush;
      }
      curr = graph[curr][i == 'R'];
      ++ans;
    }
  }
  std::cout << ans << std::endl;

  return 0;
}
