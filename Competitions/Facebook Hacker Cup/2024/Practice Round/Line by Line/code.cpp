#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const ldouble kEps = 1e-12;

struct TestCase {
  int n, p;

  ldouble BigCodeProb(ldouble p) {
    return std::pow(p / 100, n);
  }

  ldouble Solve() {
    std::cin >> n >> p;

    const ldouble target = std::pow((ldouble)p / 100, n - 1);
    ldouble lo = p, hi = 100;
    while (std::abs(hi - lo) > kEps) {
      ldouble mid = (lo + hi) / 2;
      if (BigCodeProb(mid) >= target) hi = mid;
      else lo = mid;
    }

    return lo - p;
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const ldouble ans = test_case.Solve();
    std::cout << "Case #" << t << ": " << std::setprecision(17) << ans << "\n";
  }
  return 0;
}