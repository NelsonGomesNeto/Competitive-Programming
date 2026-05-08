#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kInf = 1e6;

struct TestCase {
  int n, m;
  std::vector<std::string> grid;

  bool Valid(const std::vector<std::string>& mat, const int i, const int j) {
    if (mat[i - 1][j - 1] == '#' && mat[i - 1][j] == '#' &&
        mat[i][j - 1] == '#' && mat[i][j] == '#')
      return false;
    return true;
  }

  int CountPending(const std::vector<std::string>& mat, const int i,
                   const int j) {
    int fixes = 0;
    for (int l = 0; l < 2; ++l) {
      for (int p = 0; p < 2; ++p) {
        const int ni = i + l, nj = j + p;
        if (ni < 1 || ni >= n || nj < 1 || nj >= m) continue;
        fixes += !Valid(mat, ni, nj);
      }
    }
    return fixes;
  }

  struct State {
    std::set<std::pair<int, int>> pending;
    std::vector<std::string> mat;
    int actions;
    bool operator<(const State& other) const {
      // return (int)pending.size() < (int)other.pending.size() ||
      //        ((int)pending.size() == (int)other.pending.size() &&
      //         actions < other.actions);
      return mat < other.mat;
    }
  };
  std::set<std::pair<int, int>> BuildPending(
      const std::vector<std::string>& mat) {
    std::set<std::pair<int, int>> pending;
    for (int i = 1; i < n; ++i) {
      for (int j = 1; j < m; ++j) {
        if (Valid(mat, i, j)) continue;
        pending.emplace(i, j);
      }
    }
    return pending;
  }
  int Solve() {
    std::set<State> pq;

    pq.emplace(BuildPending(grid), grid, 0);
    int ans = kInf;
    while (!pq.empty()) {
      auto curr = *pq.begin();
      pq.erase(pq.begin());

      if (curr.pending.empty()) {
        ans = std::min(ans, curr.actions);
        continue;
      }

      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          if (curr.mat[i][j] == '.' || CountPending(curr.mat, i, j) == 0)
            continue;
          curr.mat[i][j] = '.';
          pq.emplace(BuildPending(curr.mat), curr.mat, curr.actions + 1);
          curr.mat[i][j] = '#';
        }
      }
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    grid.resize(n);
    for (auto& line : grid) std::cin >> line;

    // const int ans = Naive();
    const int ans = Solve();
    std::cout << ans << "\n";

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
    test_case.Run();
  }

  return 0;
}
