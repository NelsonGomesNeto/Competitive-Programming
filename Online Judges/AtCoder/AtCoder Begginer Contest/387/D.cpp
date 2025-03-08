#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const std::vector<std::vector<int>> kDi{{0, 0}, {-1, 1}};
const std::vector<std::vector<int>> kDj{{-1, 1}, {0, 0}};

struct TestCase {
  int n, m;
  std::vector<std::string> map;
  int si, sj, ei, ej;

  int Bfs() {
    std::vector<std::vector<std::vector<bool>>> visited(
        n, std::vector<std::vector<bool>>(m, std::vector<bool>(2, false)));
    std::queue<std::tuple<int, int, int, bool>> q;
    q.emplace(0, si, sj, false);
    q.emplace(0, si, sj, true);
    while (!q.empty()) {
      const auto [d, i, j, vertical] = q.front();
      q.pop();
      if (visited[i][j][vertical]) continue;
      visited[i][j][vertical] = true;

      if (i == ei && j == ej) {
        return d;
      }

      bool nxt_vertical = !vertical;

      for (int dir = 0; dir < kDi[nxt_vertical].size(); ++dir) {
        const int ni = i + kDi[nxt_vertical][dir], nj = j + kDj[nxt_vertical][dir];
        if (ni < 0 || ni >= n || nj < 0 || nj >= m || map[ni][nj] == '#')
          continue;
        q.emplace(d + 1, ni, nj, nxt_vertical);
      }
    }
    return -1;
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;

    map.resize(n);
    for (auto& line : map) std::cin >> line;

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (map[i][j] == 'S') si = i, sj = j;
        if (map[i][j] == 'G') ei = i, ej = j;
      }

    int ans = Bfs();
    std::cout << ans << "\n";

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
