#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, k;
  std::vector<int> a;

  bool Can(const lli x) {
    int lo = n - 1, hi = 0;
    for (int i = 0; i < n; ++i) {
      if (a[i] >= x) continue;
      lo = std::min(lo, i), hi = std::max(hi, i);
    }

    if (hi - lo + 1 > k) return false;

    for (int i = hi, add = k; add >= 1 && i >= 0; --i, --add) {
      const int newai = a[i] + add;
      if (newai < x) return false;
    }

    return true;
  }

  bool Run() {
    if (!(std::cin >> n >> k)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;

    lli lo = 0, hi = *std::max_element(a.begin(), a.end()) + k;
    while (lo < hi) {
      const lli mid = (lo + hi + 1) >> 1;
      const bool can = Can(mid);
      if (can)
        lo = mid;
      else
        hi = mid - 1;
    }
    std::cout << lo << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
