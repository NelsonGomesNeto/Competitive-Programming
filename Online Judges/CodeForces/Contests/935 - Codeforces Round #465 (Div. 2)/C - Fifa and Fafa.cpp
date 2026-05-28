#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const ldouble kEps = 1e-12;
const ldouble kPi = std::acosl(-1);

struct TestCase {
  int r, x1, y1, x2, y2;

  ldouble XonCicle(const ldouble angle) { return x1 + r * std::cosl(angle); }
  ldouble YonCicle(const ldouble angle) { return y1 + r * std::sinl(angle); }
  ldouble Eval(const ldouble angle) {
    const ldouble x = XonCicle(angle), y = YonCicle(angle);
    return std::hypotl(x - x2, y - y2);
  }

  bool Run() {
    if (!(std::cin >> r >> x1 >> y1 >> x2 >> y2)) return false;

    if (std::hypotl(x2 - x1, y2 - y1) > r) {
      std::println("{} {} {}", x1, y1, r);
      return true;
    }

    ldouble lo = 0, hi = 2 * kPi;
    while (std::abs(hi - lo) > kEps) {
      const ldouble midlo = (2 * lo + hi) / 3, midhi = (lo + 2 * hi) / 3;
      const ldouble elo = Eval(midlo), ehi = Eval(midhi);
      if (elo > ehi)
        hi = midhi;
      else
        lo = midlo;
    }
    const ldouble angle = (lo + hi) / 2;
    const ldouble radius = Eval(angle) / 2;
    const ldouble x = (x2 + XonCicle(angle)) / 2,
                  y = (y2 + YonCicle(angle)) / 2;
    std::println("{} {} {}", x, y, radius);

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
