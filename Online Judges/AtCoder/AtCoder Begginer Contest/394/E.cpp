#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kDi[] = {-1, 0, 0, 1};
const int kDj[] = {0, -1, 1, 0};
const int kInf = 1e9;

struct TestCase {
  int n;
  std::vector<std::string> c;
  std::vector<std::vector<int>> ans;
  std::vector<std::vector<int>> graph, rev_graph;
  std::vector<std::vector<std::vector<int>>> options, rev_options;

  struct State {
    int u, v, d;
  };
  std::vector<std::vector<int>> dist;
  int Dijkstra(const int start, const int end) {
    if (start == end) return 0;

    if (dist.empty()) {
      dist.resize(n, std::vector<int>(n, kInf));
    } else {
      for (auto& disti : dist) std::fill(disti.begin(), disti.end(), kInf);
    }

    std::queue<State> pq;
    pq.emplace(start, end, 0);
    int best = kInf;
    while (!pq.empty()) {
      const auto [u, v, d] = pq.front();
      pq.pop();

      if (d > dist[u][v]) continue;
      if (d + 1 > best) return best;

      if (u == v) best = std::min(best, d);
      if (c[u][v] != '-') best = std::min(best, d + 1);

      std::vector<std::vector<int>>& u_options = options[u];
      std::vector<std::vector<int>>& v_options = rev_options[v];
      for (char l = 'a'; l <= 'z'; ++l) {
        if (u_options[l].empty() || v_options[l].empty()) continue;
        for (const auto nu : u_options[l])
          for (const auto nv : v_options[l]) {
            if (d + 2 >= dist[nu][nv]) continue;
            dist[nu][nv] = d + 2;
            pq.emplace(nu, nv, d + 2);
          }
      }
    }

    return best == kInf ? -1 : best;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    c.resize(n);
    for (auto& ci : c) std::cin >> ci;

    graph.resize(n, std::vector<int>{});
    rev_graph.resize(n, std::vector<int>{});
    options.resize(n, std::vector<std::vector<int>>(256, std::vector<int>{}));
    rev_options.resize(n,
                       std::vector<std::vector<int>>(256, std::vector<int>{}));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (c[i][j] == '-') continue;
        graph[i].push_back(j), rev_graph[j].push_back(i);
        options[i][c[i][j]].push_back(j);
        rev_options[j][c[i][j]].push_back(i);
      }
      DEBUG {
        std::cout << "\t" << i << ":";
        for (const auto j : graph[i])
          std::cout << " " << j << "(" << c[i][j] << ")";
        std::cout << "\n";
      }
    }

    ans.resize(n, std::vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        ans[i][j] = Dijkstra(i, j);
        std::cout << ans[i][j] << (j + 1 == n ? '\n' : ' ');
      }
    }

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
