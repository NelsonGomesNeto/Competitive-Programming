#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kInf = 1e9;
const int kDi[4] = {0, 1, -1, 0};
const int kDj[4] = {1, 0, 0, -1};

int N, M, S;
std::vector<std::string> grid;
struct TestCase {
  void PrintGrid() {
    // std::cout << "\n";
    for (const auto& line : grid) std::cout << line << "\n";
  }

  void FillSafeSpaces() {
    std::vector<std::tuple<int, int, int>> q;
    for (int i = 0; i < N; ++i) {
      q.emplace_back(i, 0, 1), q.emplace_back(i, M - 1, 1);
      for (int j = 0; j < M; ++j) {
        q.emplace_back(0, j, 1), q.emplace_back(N - 1, j, 1);
        if (grid[i][j] == '.') continue;
        q.emplace_back(i, j, 0);
      }
    }
    std::vector<std::vector<int>> best(N, std::vector<int>(M, kInf));
    for (int qi = 0; qi < (int)q.size(); ++qi) {
      const auto [i, j, d] = q[qi];
      if (best[i][j] < d) continue;

      if (grid[i][j] == '.') {
        grid[i][j] = 'o';
      }

      if (d == S) continue;
      for (int dir = 0; dir < 4; ++dir) {
        const int ni = i + kDi[dir], nj = j + kDj[dir];
        if (ni < 0 || nj < 0 || ni >= N || nj >= M || d + 1 >= best[ni][nj])
          continue;
        best[ni][nj] = d + 1;
        q.emplace_back(ni, nj, d + 1);
      }
    }

    for (auto& line : grid)
      for (auto& c : line) {
        if (c == '#') continue;
        c = c == '.' ? '*' : '.';
      }
  }

  int Fill(const int i, const int j) {
    grid[i][j] = 'o';
    int ans = 1;
    for (int dir = 0; dir < 4; ++dir) {
      const int ni = i + kDi[dir], nj = j + kDj[dir];
      if (ni < 0 || nj < 0 || ni >= N || nj >= M || grid[ni][nj] != '*')
        continue;
      ans += Fill(ni, nj);
    }
    return ans;
  }
  int FindBiggestContinuousSpace() {
    int ans = 0;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        if (grid[i][j] != '*') continue;
        ans = std::max(ans, Fill(i, j));
      }
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> N >> M >> S)) return false;
    grid.resize(N);
    for (auto& line : grid) std::cin >> line;

    FillSafeSpaces();

    int ans = FindBiggestContinuousSpace();
    std::cout << ans << "\n";

    DEBUG PrintGrid();

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    std::cout << "Case #" << t << ": ";
    test_case.Run();
  }

  return 0;
}
