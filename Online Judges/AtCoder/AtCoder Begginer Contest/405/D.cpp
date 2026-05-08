#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kInf = 1e9;
const int kDi[4] = {0, 0, 1, -1};
const int kDj[4] = {1, -1, 0, 0};
const char kRevDir[4] = {'<', '>', '^', 'v'};

struct TestCase {
  int n, m;
  std::vector<std::string> mat;

  void Dijkstra() {
    std::vector<std::vector<int>> dist(n, std::vector<int>(m, kInf));
    std::vector<std::vector<int>> prv_dir(n, std::vector<int>(m, -1));
    std::queue<std::tuple<int, int, int>> q;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (mat[i][j] != 'E') continue;
        q.emplace(i, j, 0);
      }
    while (!q.empty()) {
      const auto [i, j, d] = q.front();
      q.pop();
      if (d > dist[i][j]) continue;

      for (int dir = 0; dir < 4; ++dir) {
        const int ni = i + kDi[dir], nj = j + kDj[dir];
        if (ni < 0 || nj < 0 || ni >= n || nj >= m || mat[ni][nj] == '#' ||
            d + 1 >= dist[ni][nj])
          continue;
        prv_dir[ni][nj] = dir;
        q.emplace(ni, nj, dist[ni][nj] = d + 1);
      }
    }

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (mat[i][j] == 'E' || prv_dir[i][j] == -1) continue;
        mat[i][j] = kRevDir[prv_dir[i][j]];
      }
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    mat.resize(n);
    for (auto& line : mat) std::cin >> line;

    Dijkstra();

    for (const auto& line : mat) std::cout << line << "\n";

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
