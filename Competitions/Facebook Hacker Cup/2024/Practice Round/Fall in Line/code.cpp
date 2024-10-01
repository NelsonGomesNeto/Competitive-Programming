#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const ldouble kEps = 1e-6;
const ldouble kPi = std::numbers::pi_v<ldouble>;
const ldouble kMaxX = 1e9;
ldouble ToDegrees(const ldouble radians) { return radians * 180 / kPi; }

struct Pos {
  ldouble x, y;
  ldouble Dist(const Pos& other) const {
    return std::sqrt((x - other.x) * (x - other.x) +
                     (y - other.y) * (y - other.y));
  }
  std::string ToString() const {
    std::ostringstream sout;
    sout << std::setprecision(16) << "(" << x << ", " << y << ")";
    return sout.str();
  }
  friend std::ostream& operator<<(std::ostream& out, const Pos& p) {
    return out << p.ToString();
  }
};
ldouble LineDistance(const Pos p1, const Pos p2, const Pos u) {
  return std::abs((p2.y - p1.y) * u.x - (p2.x - p1.x) * u.y + p2.x * p1.y -
                  p2.y * p1.x) /
         p1.Dist(p2);
}

struct TestCase {
  int n;
  std::vector<Pos> ants;
  ldouble min_x = std::numeric_limits<lli>::max(),
          max_x = std::numeric_limits<lli>::min();

  struct EvalResp {
    ldouble distance_sum;
    int to_move;
    ldouble angle, x;
    Pos p1, p2;
  };
  EvalResp Eval(const ldouble angle, const ldouble x) {
    Pos p1 = {x, (ldouble)0}, p2 = {x + std::cos(angle), std::sin(angle)};
    // std::cout << "p1: " << p1 << " | p2: " << p2 << "\n";

    ldouble distance_sum = 0;
    int to_move = 0;
    for (const Pos& p : ants) {
      const ldouble dist = LineDistance(p1, p2, p);
      // std::cout << "\tdist: " << dist << "\n";
      if (dist <= kEps) continue;
      distance_sum += dist;
      ++to_move;
    }
    return EvalResp{distance_sum, to_move, angle, x, p1, p2};
  }
  EvalResp Eval(const ldouble angle) {
    ldouble lo = -kMaxX, hi = kMaxX;
    while (std::abs(hi - lo) >= kEps) {
      ldouble midlo = (2 * lo + hi) / 3, midhi = (lo + 2 * hi) / 3;
      ldouble elo = Eval(angle, midlo).distance_sum,
              ehi = Eval(angle, midhi).distance_sum;
      if (elo <= ehi) hi = midhi;
      if (ehi <= elo) lo = midlo;
    }
    // std::cout << std::setprecision(16) << "angle: " << angle << " | x: " <<
    // lo
    //           << "\n";
    return Eval(angle, (lo + hi) / 2);
  }
  int Solve() {
    std::cin >> n;
    ants.resize(n);
    for (Pos& p : ants) {
      std::cin >> p.x >> p.y;
      min_x = std::min(min_x, p.x);
      max_x = std::max(max_x, p.x);
    }

    ldouble lo = 0, hi = kPi;
    while (std::abs(hi - lo) >= kEps) {
      ldouble midlo = (2 * lo + hi) / 3, midhi = (lo + 2 * hi) / 3;
      ldouble elo = Eval(midlo).distance_sum, ehi = Eval(midhi).distance_sum;
      if (elo <= ehi) hi = midhi;
      if (ehi <= elo) lo = midlo;
    }
    EvalResp res = Eval((lo + hi) / 2);
    // std::cout << std::setprecision(16) << res.angle << " " << res.x << " | "
    //           << res.p1 << " " << res.p2 << " | " << res.distance_sum << " | "
    //           << res.to_move << "\n";

    // return Eval(0.4654211338649715, 4.666666666666361);
    // return Eval(0.9827937232473291, -0.6666666666666664).to_move;

    return res.to_move;
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const int ans = test_case.Solve();
    std::cout << "Case #" << t << ": " << ans << "\n";
  }
  return 0;
}