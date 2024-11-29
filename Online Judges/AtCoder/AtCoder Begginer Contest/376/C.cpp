#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<int> a, b;

  bool Can(const int x) {
    for (int i = 0, j = 0; i < n; ++i, ++j) {
      if (i == x) {
        --j;
        continue;
      }
      if (a[i] > b[j]) return false;
    }
    return true;
  }
  int BinarySearch() {
    int lo = 0, hi = n - 1;
    while (lo < hi) {
      int mid = (lo + hi) >> 1;
      if (Can(mid))
        hi = mid;
      else
        lo = mid + 1;
    }
    return Can(lo) ? a[lo] : -1;
  }

  bool Solve() {
    if (!(std::cin >> n)) return false;
    a.resize(n), b.resize(n - 1);
    for (int& ai : a) std::cin >> ai;
    for (int& bi : b) std::cin >> bi;
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    int ans = BinarySearch();
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  do {
    test_case = TestCase{};
  } while (test_case.Solve());
  return 0;
}
