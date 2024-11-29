#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, q;
  std::string s;

  std::vector<std::vector<int>> acc;
  std::vector<int> slashes;
  int GetRangeSum(const int kind, const int lo, const int hi) {
    return acc[kind][hi + 1] - acc[kind][lo];
  }
  int Evaluate(const int pos, const int lo, const int hi) {
    const int ones = GetRangeSum(0, lo, pos), twos = GetRangeSum(1, pos, hi);
    return 2 * std::min(ones, twos) + 1;
  }
  void Solve() {
    acc.resize(2, std::vector<int>(n + 1, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 2; ++j) {
        acc[j][i + 1] = acc[j][i] + (s[i] - '1' == j);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (s[i] != '/') continue;
      slashes.push_back(i);
    }

    for (int qq = 0; qq < q; ++qq) {
      int range_lo, range_hi;
      std::cin >> range_lo >> range_hi;
      --range_lo, --range_hi;

      auto Eval = [&](const int i) {
        return Evaluate(slashes[i], range_lo, range_hi);
      };

      auto loit = std::lower_bound(slashes.begin(), slashes.end(), range_lo);
      if (loit == slashes.end() || *loit > range_hi) {
        std::cout << "0\n";
        continue;
      }
      int lo = loit - slashes.begin(),
          hi = std::prev(
                   std::upper_bound(slashes.begin(), slashes.end(), range_hi)) -
               slashes.begin();
      auto Valid = [&](const int i) {
        return i >= 0 && i < (int)slashes.size() && slashes[i] >= range_lo &&
               slashes[i] <= range_hi;
      };
      assert(Valid(lo) && Valid(hi));
      // while (hi - lo > 3) {
      //   int midlo = (2 * lo + hi) / 3, midhi = (lo + 2 * hi) / 3;
      //   int elo = Eval(midlo), ehi = Eval(midhi);
      //   if (elo >= ehi) hi = midhi;
      //   if (ehi >= elo) lo = midlo;
      // }
      int res = Eval(lo);
      for (int i = lo + 1; i <= hi; ++i) res = std::max(res, Eval(i));
      std::cout << res << "\n";
    }
  }

  bool Run() {
    if (!(std::cin >> n >> q)) return false;
    std::cin >> s;

    Solve();

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
