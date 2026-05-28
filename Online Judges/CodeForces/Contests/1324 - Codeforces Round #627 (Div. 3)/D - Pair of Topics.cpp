#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<int> a, b;
  std::vector<int> aminusb;
  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n), b.resize(n), aminusb.resize(n);
    for (int& ai : a) std::cin >> ai;
    for (int& bi : b) std::cin >> bi;
    for (auto [abi, ai, bi] : std::views::zip(aminusb, a, b)) {
      abi = ai - bi;
    }

    std::ranges::sort(aminusb);
    lli ans = 0;
    for (const auto [i, abi] :
         aminusb | std::views::take(n - 1) | std::views::enumerate) {
      // abi + abj > 0
      int lo = i + 1, hi = n - 1;
      while (lo < hi) {
        const int mid = (lo + hi) >> 1;
        if (abi + aminusb[mid] > 0)
          hi = mid;
        else
          lo = mid + 1;
      }
      if (abi + aminusb[lo] <= 0) continue;
      ans += n - lo;
    }
    std::println("{}", ans);

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
