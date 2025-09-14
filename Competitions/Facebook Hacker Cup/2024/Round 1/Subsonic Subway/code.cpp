#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const ldouble kEps = 1e-12;

struct TestCase {
  int n;
  std::vector<std::pair<int, int>> ab;

  ldouble Eval(const ldouble speed) {
    int valid = 0;
    ldouble dist = 0;
    for (int i = 0; i < ab.size(); ++i) {
      const ldouble t = (i + 1) / speed;
      if (t >= ab[i].first && t <= ab[i].second) {
        ++valid;
      } else {
        // dist += std::abs(t - (ab[i].first + ab[i].second) / 2);
        dist += std::min(std::abs(t - ab[i].first), std::abs(t - ab[i].second));
      }
    }
    return dist;
  }

  ldouble Solve() {
    std::cin >> n;
    ab.resize(n);
    for (auto& [a, b] : ab) std::cin >> a >> b;

    ldouble lo = 0, hi = n;
    while (std::abs(hi - lo) > kEps) {
      ldouble midlo = (2 * lo + hi) / 3, midhi = (lo + 2 * hi) / 3;
      ldouble elo = Eval(midlo), ehi = Eval(midhi);
      if (elo <= ehi)
        hi = midhi;
      else
        lo = midlo;
    }
    if (Eval(lo) != 0) return -1;
    return lo;
  }
};
TestCase test_case;

int main() {
  std::cout << std::setprecision(5);
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const auto ans = test_case.Solve();
    std::cout << "Case #" << t << ": " << ans << "\n";
  }
  return 0;
}
