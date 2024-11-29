#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::vector<std::pair<int, int>> pieces;

  std::vector<int> rows, cols;
  std::vector<std::pair<int, int>> diag1, diag2;
  std::vector<std::pair<int, int>> intersections;

  std::vector<std::pair<int, int>> rows_intersections, cols_intersections,
      diag1_intersections, diag2_intersections;

  template <class T>
  void MakeUnique(std::vector<T>& arr) {
    std::sort(arr.begin(), arr.end());
    arr.resize(std::distance(arr.begin(), std::unique(arr.begin(), arr.end())));
  }

  void AddIntersection(const int i, const int j) {
    intersections.emplace_back(i, j);
  }

  void AddRowAndColumnIntersection(const int ai, const int bi) {
    const auto& [i, j] = pieces[ai];
    const auto& [oi, oj] = pieces[bi];
    AddIntersection(i, oj);
  }

  void AddRowAndDiag1Intersection(const int ai, const int bi) {
    const auto& [i, j] = pieces[ai];
    const auto& [oi, oj] = pieces[bi];
    /* find y = odelta
      { i = oi + y, y = i - oi
      { j + x = oj + y
    */
    const int odelta = i - oi;

    const int mi = oi + odelta, mj = oj + odelta;
    if (mi < 0 || mj < 0 || mi >= n || mj >= n) return;

    AddIntersection(mi, mj);
  }
  void AddColAndDiag1Intersection(const int ai, const int bi) {
    const auto& [i, j] = pieces[ai];
    const auto& [oi, oj] = pieces[bi];
    /* find y = odelta
      { i + x = oi + y
      { j = oj + y, y = j - oj
    */
    const int odelta = j - oj;

    const int mi = oi + odelta, mj = oj + odelta;
    if (mi < 0 || mj < 0 || mi >= n || mj >= n) return;

    AddIntersection(mi, mj);
  }

  void AddRowAndDiag2Intersection(const int ai, const int bi) {
    const auto& [i, j] = pieces[ai];
    const auto& [oi, oj] = pieces[bi];
    /* find y = odelta
      { i = oi - y, y = oi - i
      { j + x = oj + y
    */
    const int odelta = oi - i;

    const int mi = oi - odelta, mj = oj + odelta;
    if (mi < 0 || mj < 0 || mi >= n || mj >= n) return;

    AddIntersection(mi, mj);
  }
  void AddColAndDiag2Intersection(const int ai, const int bi) {
    const auto& [i, j] = pieces[ai];
    const auto& [oi, oj] = pieces[bi];
    /* find y = odelta
      { i + x = oi - y
      { j = oj + y, y = j - oj
    */
    const int odelta = j - oj;

    const int mi = oi - odelta, mj = oj + odelta;
    if (mi < 0 || mj < 0 || mi >= n || mj >= n) return;

    AddIntersection(mi, mj);
  }

  void AddDiag1AndDiag2Intersection(const int ai, const int bi) {
    const auto& [i, j] = pieces[ai];
    const auto& [oi, oj] = pieces[bi];
    /* find y = odelta
      { i + x = oi - y, x = oi - y - i
      { j + x = oj + y
      j + oi - y - i = oj + y
      (j - oj) + (oi - i) = 2y
    */
    const lli quotient = (j - oj) + (oi - i);
    if (quotient & 1) return;
    const int odelta = (quotient) / 2;

    const int mi = oi - odelta, mj = oj + odelta;
    if (mi < 0 || mj < 0 || mi >= n || mj >= n) return;

    AddIntersection(mi, mj);
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    pieces.resize(m);
    for (auto& [i, j] : pieces) {
      std::cin >> i >> j;
      --i, --j;
    }

    for (int ai = 0; ai < m; ++ai) {
      const auto& [i, j] = pieces[ai];
      rows.push_back(i);
      cols.push_back(j);
      diag1.emplace_back(i - j,
                         std::min(i, j) + std::min(n - 1 - i, n - 1 - j) + 1);
      diag2.emplace_back(i + j,
                         std::min(i, n - 1 - j) + std::min(n - 1 - i, j) + 1);
      AddIntersection(i, j);

      for (int bi = 0; bi < m; ++bi) {
        AddRowAndColumnIntersection(ai, bi);

        AddRowAndDiag1Intersection(ai, bi);

        AddColAndDiag1Intersection(ai, bi);

        AddRowAndDiag2Intersection(ai, bi);

        AddColAndDiag2Intersection(ai, bi);

        AddDiag1AndDiag2Intersection(ai, bi);
        AddDiag1AndDiag2Intersection(bi, ai);
      }
    }

    MakeUnique(rows);
    MakeUnique(cols);
    MakeUnique(diag1);
    MakeUnique(diag2);
    MakeUnique(intersections);
    {
      std::vector<int> all_rows, all_cols, all_diag1, all_diag2;
      for (const auto& [i, j] : intersections) {
        all_rows.push_back(i);
        all_cols.push_back(j);
        all_diag1.push_back(i - j);
        all_diag2.push_back(i + j);
      }
      auto CntAndAdd = [&](std::vector<int>& arr,
                           std::vector<std::pair<int, int>>& cnt_map) {
        std::sort(arr.begin(), arr.end());
        for (int i = 0; i < arr.size(); ++i) {
          int j = i;
          while (j + 1 < arr.size() && arr[j + 1] == arr[i]) ++j;
          cnt_map.emplace_back(arr[i], j - i + 1);
          i = j;
        }
      };
      CntAndAdd(all_rows, rows_intersections);
      CntAndAdd(all_cols, cols_intersections);
      CntAndAdd(all_diag1, diag1_intersections);
      CntAndAdd(all_diag2, diag2_intersections);
    }

    DEBUG2 std::cout << "\t" << intersections.size() << "\n";
    DEBUG2 std::cout << "\t" << rows.size() << " " << cols.size() << " "
                     << diag1.size() << " " << diag2.size() << "\n";
    DEBUG2 std::cout << "\t" << rows_intersections.size() << " "
                     << cols_intersections.size() << " "
                     << diag1_intersections.size() << " "
                     << diag2_intersections.size() << "\n";

    lli ans = (lli)n * n - (int)intersections.size();
    for (const int ri : rows) {
      int rem = n;
      auto it =
          std::lower_bound(rows_intersections.begin(), rows_intersections.end(),
                           std::make_pair(ri, -1));
      if (it != rows_intersections.end()) rem -= it->second;
      DEBUG std::cout << "\trows: " << ri << " | " << rem << "\n";
      ans -= rem;
    }
    for (const int cj : cols) {
      int rem = n;
      auto it =
          std::lower_bound(cols_intersections.begin(), cols_intersections.end(),
                           std::make_pair(cj, -1));
      if (it != cols_intersections.end()) rem -= it->second;
      DEBUG std::cout << "\tcols: " << cj << " | " << rem << "\n";
      ans -= rem;
    }
    for (const auto& [diag1_i_minus_j, cnt] : diag1) {
      int rem = cnt;
      auto it = std::lower_bound(diag1_intersections.begin(),
                                 diag1_intersections.end(),
                                 std::make_pair(diag1_i_minus_j, -1));
      if (it != diag1_intersections.end()) rem -= it->second;
      DEBUG std::cout << "\tdiag1: " << diag1_i_minus_j << " | " << cnt << " | "
                      << rem << "\n";
      ans -= rem;
    }
    for (const auto& [diag2_i_plus_j, cnt] : diag2) {
      int rem = cnt;
      auto it = std::lower_bound(diag2_intersections.begin(),
                                 diag2_intersections.end(),
                                 std::make_pair(diag2_i_plus_j, -1));
      if (it != diag2_intersections.end()) rem -= it->second;
      DEBUG std::cout << "\tdiag2: " << diag2_i_plus_j << " | " << cnt << " | "
                      << rem << "\n";
      ans -= rem;
    }

    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
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