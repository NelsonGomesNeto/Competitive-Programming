#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::vector<std::pair<int, int>> pieces;

  std::unordered_set<int> rows, cols;
  std::unordered_set<int> diag1, diag2;

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    pieces.resize(m);
    for (auto& [i, j] : pieces) {
      std::cin >> i >> j;
      --i, --j;
    }

    for (int ai = 0; ai < m; ++ai) {
      const auto& [i, j] = pieces[ai];
      rows.insert(i);
      cols.insert(j);
      diag1.insert(i - j);
      diag2.insert(i + j);
    }

    lli ans = (lli)(n - (int)rows.size()) * (n - (int)cols.size());
    for (const int diag1_i_minus_j : diag1) {
      std::unordered_set<int> intersections;
      for (const int ri : rows) {
        /*
        d = i - j
        ri - k = d
        k = ri - d
        */
        const int j = ri - diag1_i_minus_j;
        if (j < 0 || j >= n) continue;
        intersections.insert(j);
      }
      for (const int cj : cols) {
        /*
        d = i - j
        k - cj = d
        k = d + cj
        */
        const int i = diag1_i_minus_j + cj;
        if (i < 0 || i >= n) continue;
        intersections.insert(cj);
      }
      /*
      cnt = min(i, j) + min(n - 1 - i, n - 1 - j) + 1
      if i < j:
        cnt = i + n - 1 - j + 1
        cnt = i - j + n, note that (i - j) is negative
      if j < i:
        cnt = j + n - 1 - i + 1
        cnt = j - i + n, note that (j - i) is negative
      so, cnt = n - abs(i - j)
      */
      const int cnt = n - std::abs(diag1_i_minus_j);
      ans -= cnt - (int)intersections.size();
    }
    for (const int diag2_i_plus_j : diag2) {
      std::unordered_set<int> intersections;
      for (const int ri : rows) {
        /*
        d = i + j
        ri + k = d
        k = d - ri
        */
        const int j = diag2_i_plus_j - ri;
        if (j < 0 || j >= n) continue;
        intersections.insert(j);
      }
      for (const int cj : cols) {
        /*
        d = i + j
        k + cj = d
        k = d - cj
        */
        const int i = diag2_i_plus_j - cj;
        if (i < 0 || i >= n) continue;
        intersections.insert(cj);
      }
      for (const int diag1_i_minus_j : diag1) {
        /*
        d1 = oi - oj
        d2 = i + j
        d2 + d1 = i + oi, forcing them to be a the same position
        d2 - d1 = j + oj, forcing them to be a the same position
        */
        const int sum = diag2_i_plus_j + diag1_i_minus_j;
        if (sum & 1) continue;
        const int i = sum / 2;
        if (i < 0 || i >= n) continue;

        const int minus = diag2_i_plus_j - diag1_i_minus_j;
        const int j = minus / 2;
        if (j < 0 || j >= n) continue;
        intersections.insert(j);
      }
      /*
      cnt = min(i, n - 1 - j) + min(n - 1 - i, j) + 1
      if i < n - 1 - j: (that implies j < n - 1 - i)
        cnt = i + j + 1
      if n - 1 - j < i: (that implies n - 1 - i < j)
        cnt = n - 1 - j + n - 1 - i + 1
        cnt = 2*n - (i + j) - 1
      so, cnt = 2*min(i + j, n - 1) - (i + j) + 1
      */
      const int cnt = 2 * std::min(diag2_i_plus_j, n - 1) - diag2_i_plus_j + 1;
      ans -= cnt - (int)intersections.size();
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