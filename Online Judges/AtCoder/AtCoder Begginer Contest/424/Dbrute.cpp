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

  struct State {
    FastGrid mat;
    int actions;
    int si, sj;
    bool operator<(const State& other) const { return actions < other.actions; }
  };
  std::vector<std::tuple<int, int, int>> mutable_pos;
  int Solve() {
    std::unordered_set<lli> done;
    std::vector<State> pq;
    pq.reserve(kMaxStates);  // This is absolutely important to avoid
                             // unnecessary alocs.
    pq.emplace_back(fast_grid, 0, 1, 1);
    for (int qi = 0; qi < pq.size(); ++qi) {
      auto curr = pq[qi];

      const auto [bi, bj] = AllValid(curr.mat);
      if (bi == -1) {
        return curr.actions;
      }
      // There is no way to fix this invalid block.
      if (bi + 1 < curr.si ||
          ((bi == curr.si || bi + 1 == curr.si) && bj + 1 < curr.sj))
        continue;

      const int endi = n == 2 ? n : n - 1, endj = m == 2 ? m : m - 1;
      for (int i = curr.si; i < endi; ++i) {
        for (int j = (i == curr.si ? curr.sj : 1); j < endj; ++j) {
          if (curr.mat.Get(i, j) == '.') continue;
          curr.mat.Flip(i, j);
          pq.emplace_back(curr.mat, curr.actions + 1, i, j + 1);
          curr.mat.Flip(i, j);
        }
      }
    }
    assert(false);
    return -1;
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
