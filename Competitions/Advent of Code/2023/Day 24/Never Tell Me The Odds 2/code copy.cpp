#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

enum Coordinate { X, Y, Z };
char CoordinateName(const Coordinate coordinate) {
  switch (coordinate) {
    case Coordinate::X:
      return 'X';
    case Coordinate::Y:
      return 'Y';
    case Coordinate::Z:
    default:
      return 'Z';
  }
}
struct Vec {
  lli x, y, z;

  static lli ReadCoordinate(std::istringstream& isin) {
    lli coordinate;
    isin >> coordinate;
    isin.ignore(10, ',');
    return coordinate;
  }
  Vec(const lli x_, const lli y_, const lli z_) : x(x_), y(y_), z(z_) {}
  Vec() : Vec(0, 0, 0) {}
  Vec(std::istringstream&& isin)
      : x(ReadCoordinate(isin)),
        y(ReadCoordinate(isin)),
        z(ReadCoordinate(isin)) {}
  Vec(const std::string& str) : Vec(std::istringstream(str)) {}

  std::string ToString() const {
    std::ostringstream sout;
    sout << "(" << std::setfill(' ') << std::setw(2) << x;
    sout << ", " << std::setfill(' ') << std::setw(2) << y;
    sout << ", " << std::setfill(' ') << std::setw(2) << z << ")";
    return sout.str();
  }
  friend std::ostream& operator<<(std::ostream& out, const Vec& v) {
    return out << v.ToString();
  }

  bool operator<(const Vec& other) const {
    return x < other.x || (x == other.x && y < other.y) ||
           (x == other.x && y == other.y && z < other.z);
  }
  bool operator==(const Vec& other) const {
    return x == other.x && y == other.y && z == other.z;
  }

  lli Get(const Coordinate coordinate) const {
    switch (coordinate) {
      case Coordinate::X:
        return x;
      case Coordinate::Y:
        return y;
      case Coordinate::Z:
      default:
        return z;
    }
  }
  void Set(const Coordinate coordinate, const lli value) {
    switch (coordinate) {
      case Coordinate::X:
        x = value;
        return;
      case Coordinate::Y:
        y = value;
        return;
      case Coordinate::Z:
      default:
        z = value;
        return;
    }
  }

  double Dist(const Vec& other) const {
    const double xx = (x - other.x), yy = (y - other.y), zz = (z - other.z);
    return sqrt(xx * xx + yy * yy + zz * zz);
  }
};
struct Hailstone {
  Vec pos, vel;

  static Vec ReadVec(std::istringstream& isin) {
    std::string vec_str;
    std::getline(isin, vec_str, '@');
    return Vec(vec_str);
  }
  Hailstone(std::istringstream&& isin)
      : pos(ReadVec(isin)), vel(ReadVec(isin)) {}
  Hailstone(const std::string& str) : Hailstone(std::istringstream(str)) {}
  Hailstone() {}

  std::string ToString() const {
    std::ostringstream sout;
    sout << pos << " @ " << vel;
    return sout.str();
  }
  friend std::ostream& operator<<(std::ostream& out, const Hailstone& h) {
    return out << h.ToString();
  }

  bool operator<(const Hailstone& other) const {
    return pos < other.pos || (pos == other.pos && vel < other.vel);
  }

  Vec AfterTime(const lli t) const {
    return Vec{pos.x + vel.x * t, pos.y + vel.y * t, pos.z + vel.z * t};
  }
  double MinDist(const Hailstone& other) const {
    lli t = 0;
    for (const Coordinate c : {Coordinate::X, Coordinate::Y, Coordinate::Z}) {
      const lli denominator = vel.Get(c) - other.vel.Get(c);
      if (denominator == 0) continue;
      const lli numerator = other.pos.Get(c) - pos.Get(c);
      t = std::round((double)numerator / denominator);
      break;
    }
    const Vec this_pos = AfterTime(t);
    const Vec other_pos = other.AfterTime(t);
    return this_pos.Dist(other_pos);

    // Old Ternary Search method hihi
    {
      auto eval = [&](const lli t) {
        const Vec this_pos = AfterTime(t);
        const Vec other_pos = other.AfterTime(t);
        return this_pos.Dist(other_pos);
      };
      lli lo = 1, hi = 10;
      while (hi - lo > 3) {
        const lli midlo = (2 * lo + hi) / 3, midhi = (lo + 2 * hi) / 3;
        const double elo = eval(midlo), ehi = eval(midhi);
        if (elo < ehi)
          hi = midhi;
        else
          lo = midlo;
      }
      lli res = lo;
      double best = eval(lo);
      for (lli i = lo + 1; i <= hi; ++i) {
        const double ei = eval(i);
        if (ei >= best) continue;
        best = ei, res = i;
      }
      return best;
    }
  }
};
struct Hailstones {
  const std::vector<Hailstone> hs;

  static Hailstones Read() {
    std::vector<Hailstone> hs;
    for (std::string line; std::getline(std::cin, line);) {
      hs.emplace_back(line);
    }
    return Hailstones{hs};
  }

  std::string ToString() const {
    std::ostringstream sout;
    for (int i = 0; i < hs.size(); ++i) {
      const Hailstone& h = hs[i];
      sout << i << " | " << h << "\n";
    }
    return sout.str();
  }
  friend std::ostream& operator<<(std::ostream& out, const Hailstones& h) {
    return out << h.ToString();
  }

  std::pair<lli, lli> GetPosBounds(const Coordinate c) const {
    lli lo = std::numeric_limits<lli>::max(),
        hi = std::numeric_limits<lli>::min();
    for (const Hailstone& h : hs) {
      lo = std::min(lo, h.pos.Get(c));
      hi = std::max(hi, h.pos.Get(c));
    }
    return std::make_pair(lo - 10, hi + 10);
    // return std::make_pair(0, 30);
  }
  std::pair<lli, lli> GetVelBounds(const Coordinate c) const {
    lli lo = std::numeric_limits<lli>::max(),
        hi = std::numeric_limits<lli>::min();
    for (const Hailstone& h : hs) {
      lo = std::min(lo, h.vel.Get(c));
      hi = std::max(hi, h.vel.Get(c));
    }
    return std::make_pair(lo - 10, hi + 10);
    // return std::make_pair(-3, 2);
  }
  struct TernarySearchParams {
    const lli lo, hi;
    const bool pos;
    const Coordinate coordinate;
    Hailstone& h;
    std::function<double(const lli)> eval;

    std::map<Hailstone, double> memo;

    void Update(const lli value) const {
      if (pos)
        h.pos.Set(coordinate, value);
      else
        h.vel.Set(coordinate, value);
    }
    double Eval(const lli value) {
      Update(value);
      auto it = memo.find(h);
      if (it != memo.end()) return it->second;
      const double res = eval(value);
      memo.emplace(h, res);
      return res;
    }
  };
  double SumMinDist(const Hailstone& bullet) const {
    double res = 0;
    // for (int i = 0; i < 10; ++i) {
    //   res += bullet.MinDist(hs[i]);
    // }
    for (const Hailstone& h : hs) res += bullet.MinDist(h);
    return res;
  }
  Hailstone FindBullet() const {
    for (const Coordinate c : {Coordinate::X, Coordinate::Y, Coordinate::Z}) {
      std::cout << "Coordinate: " << CoordinateName(c) << "\n";
      const auto [pos_lo, pos_hi] = GetPosBounds(c);
      const auto [vel_lo, vel_hi] = GetVelBounds(c);
      const lli pos_search_space = pos_hi - pos_lo + 1,
                vel_search_space = vel_hi - vel_lo + 1;
      std::cout << "pos_lo: " << pos_lo << " | pos_hi: " << pos_hi
                << " | search_space: " << pos_search_space
                << " | log2: " << std::log2(pos_search_space) << "\n";
      std::cout << "vel_lo: " << vel_lo << " | vel_hi: " << vel_hi
                << " | search_space: " << vel_search_space
                << " | log2: " << std::log2(vel_search_space) << "\n";
    }
    std::fflush(stdout);

    // Try to stop depending on these many returns
    // Also prefer Hailstone instead of std::pair<Vec, Vec>
    // As a bonus: can transform Vec into completely const again?
    Hailstone bullet;
    auto ternary_search = [&](TernarySearchParams& params) {
      lli lo = params.lo, hi = params.hi;
      while (hi - lo > 3) {
        const lli midlo = (2 * lo + hi) / 3, midhi = (lo + 2 * hi) / 3;
        const double elo = params.Eval(midlo), ehi = params.Eval(midhi);
        if (elo < ehi)
          hi = midhi;
        else
          lo = midlo;
      }
      lli res = lo;
      double best = params.Eval(lo);
      for (lli i = lo + 1; i <= hi; ++i) {
        const double ei = params.Eval(i);
        if (ei >= best) continue;
        best = ei, res = i;
      }
      // This is required to update the Hailstone while it returns.
      return params.Eval(res);
    };

    std::vector<TernarySearchParams> tsps;
    for (const auto c : {Coordinate::X, Coordinate::Y, Coordinate::Z}) {
      const auto [pos_lo, pos_hi] = GetPosBounds(c);
      const auto [vel_lo, vel_hi] = GetVelBounds(c);
      for (const auto [lo, hi, on_pos] :
           std::vector<std::tuple<lli, lli, bool>>{{pos_lo, pos_hi, true},
                                                   {vel_lo, vel_hi, false}})
        tsps.emplace_back(lo, hi, on_pos, c, bullet);
    }

    for (int i = tsps.size() - 1; i >= 0; --i) {
      TernarySearchParams& tsp = tsps[i];
      if (i + 1 == tsps.size()) {
        tsp.eval = [&](const lli value) { return SumMinDist(bullet); };
      } else {
        tsp.eval = [&, &next_tsp = tsps[i + 1]](const lli value) {
          return ternary_search(next_tsp);
        };
      }
    }

    ternary_search(tsps[0]);

    return bullet;
  }

  lli Solve() const {
    lli ans = 0;

    const Hailstone bullet = FindBullet();
    // const Vec u{24, 13, 10}, du{-3, 1, 2};
    std::cout << "bullet: " << bullet
              << " | sum_min_dist: " << SumMinDist(bullet) << "\n";

    return bullet.pos.x + bullet.pos.y + bullet.pos.z;
  }
};

int main() {
  const Hailstones hailstones = Hailstones::Read();

  std::cout << hailstones;

  const lli ans = hailstones.Solve();
  std::cout << "ans: " << ans << "\n";

  return 0;
}
