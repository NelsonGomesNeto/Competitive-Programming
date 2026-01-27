#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kInf = 1e6, kMaxAns = 9, kMaxStates = 3e5;

int n, m;

struct TestCase {
  std::vector<std::string> grid;
  struct FastGrid {
    lli grid = 0;
    bool operator<(const FastGrid& other) const { return grid < other.grid; }
    char Get(const int i, const int j) const {
      return (grid & (1LL << (i * m + j))) == 0 ? '#' : '.';
    }
    FastGrid GetRow(const int i) {
      // return FastGrid{grid};
      // return FastGrid{((1LL << ((i + 1) * m)) - 1) & ~((1LL << ((i)*m)) -
      // 1)};
      return FastGrid{((1LL << ((i + 1) * m)) - 1) & ~((1LL << ((i)*m)) - 1) &
                      grid};
    }
    void Set(const int i, const int j, const char v) {
      if (Get(i, j) == v) return;
      Flip(i, j);
    }
    void Flip(const int i, const int j) { grid ^= (1LL << (i * m + j)); }
  };
  FastGrid fast_grid;

  std::vector<std::vector<lli>> memo_valid_masks;
  void PrecalcValidMasks() {
    memo_valid_masks.resize(n, std::vector<lli>(m, 0));
    for (int i = 1; i < n; ++i) {
      for (int j = 1; j < m; ++j) {
        lli& mask = memo_valid_masks[i][j];
        for (int ii = i - 1; ii <= i; ++ii)
          for (int jj = j - 1; jj <= j; ++jj) {
            mask |= 1LL << (ii * m + jj);
          }
      }
    }
  }
  bool Valid(const FastGrid& mat, const int i, const int j) {
    return ((~mat.grid) & memo_valid_masks[i][j]) != memo_valid_masks[i][j];
    // if (((~mat.grid) & memo_valid_masks[i][j]) == memo_valid_masks[i][j])
    //   return false;
    // if (mat.Get(i - 1, j - 1) == '#' && mat.Get(i - 1, j) == '#' &&
    //     mat.Get(i, j - 1) == '#' && mat.Get(i, j) == '#')
    //   return false;
    // return true;
  }

  std::pair<int, int> AllValid(const FastGrid& mat) {
    for (int i = 1; i < n; ++i) {
      for (int j = 1; j < m; ++j) {
        if (!Valid(mat, i, j)) return {i, j};
      }
    }
    return {-1, -1};
  }

  std::vector<std::vector<int>> memo;
  int Solve(FastGrid prv_row, int i = 1) {
    if (i == n) {
      return 0;
    }
    int& ans = memo[i][prv_row.GetRow(i - 1).grid >> ((i - 1) * m)];
    if (ans != -1) return ans;

    ans = kMaxAns;
    const FastGrid curr_row = fast_grid.GetRow(i);
    for (lli mask = 0, end = 1LL << m; mask < end; ++mask) {
      FastGrid fixed = FastGrid{prv_row.grid | curr_row.grid};
      fixed.grid |= mask << (i * m);
      bool all_valid = true;
      int cost = 0;
      for (int j = 0; j < m; ++j) {
        if (j &&
            (!(fixed.Get(i, j) == '.' || fixed.Get(i, j - 1) == '.') &&
             !(fixed.Get(i - 1, j) == '.' || fixed.Get(i - 1, j - 1) == '.')))
          all_valid = false;
        if (curr_row.Get(i, j) == '.' && fixed.Get(i, j) == '#')
          all_valid = false;
        cost += (curr_row.Get(i, j) == '#' && fixed.Get(i, j) == '.');
      }
      if (!all_valid) continue;

      const int res = Solve(fixed.GetRow(i), i + 1) + cost;
      ans = std::min(ans, res);
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    PrecalcValidMasks();
    grid.resize(n);
    for (auto& line : grid) std::cin >> line;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        fast_grid.Set(i, j, grid[i][j]);
      }
    }

    // for (int i = 0; i < n; ++i) {
    //   std::string hehe =
    //       std::format("{:0{}b}", fast_grid.GetRow(i).grid, (i + 1) * m)
    //           .substr(0, m);
    //   std::reverse(hehe.begin(), hehe.end());
    //   std::println("{}", hehe);
    // }
    memo.resize(n, std::vector<int>(1LL << m, -1));
    const int ans = Solve(fast_grid.GetRow(0));
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
