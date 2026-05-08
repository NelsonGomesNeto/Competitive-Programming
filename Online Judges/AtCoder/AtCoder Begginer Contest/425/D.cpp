#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kDi[4] = {-1, 0, 0, 1};
const int kDj[4] = {0, 1, -1, 0};

struct TestCase {
  int n, m;
  std::vector<std::string> grid;
  std::vector<std::vector<int>> g;

  void Print() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        std::cout << (g[i][j] == 0 ? '.' : '#');
      }
      std::cout << "\n";
    }
  }

  int Cnt(const int i, const int j, const int it) {
    int cnt = 0;
    for (int d = 0; d < 4; ++d) {
      const int ni = i + kDi[d], nj = j + kDj[d];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      cnt += g[ni][nj] > 0 && g[ni][nj] <= it;
    }
    return cnt;
  }

  int FloodFill() {
    std::vector<std::tuple<int, int, int>> q;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        DEBUG std::cout << "\t\t" << i << " " << j << " " << Cnt(i, j, 1)
                        << "\n";
        if (grid[i][j] != '.' || Cnt(i, j, 1) != 1) continue;
        q.emplace_back(i, j, 1);
      }
    }
    for (int qi = 0; qi < (int)q.size(); ++qi) {
      const auto [i, j, it] = q[qi];
      DEBUG std::cout << "\t" << i << " " << j << " " << it << "\n";
      if (Cnt(i, j, it) != 1) continue;
      g[i][j] = it + 1;
      for (int d = 0; d < 4; ++d) {
        const int ni = i + kDi[d], nj = j + kDj[d];
        if (ni < 0 || ni >= n || nj < 0 || nj >= m || g[ni][nj] > 0 ||
            Cnt(ni, nj, it + 1) != 1)
          continue;
        q.emplace_back(ni, nj, it + 1);
      }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        ans += g[i][j] > 0;
      }
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    grid.resize(n), g.resize(n, std::vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
      auto& line = grid[i];
      std::cin >> line;
      for (int j = 0; j < m; ++j) {
        g[i][j] = grid[i][j] == '#' ? 1 : 0;
      }
    }

    const int ans = FloodFill();
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
