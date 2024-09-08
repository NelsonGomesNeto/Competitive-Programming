#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

// const double kRangeMin = 7, kRangeMax = 27;
const double kRangeMin = 200000000000000, kRangeMax = 400000000000000;

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
  const double x, y, z;

  static double ReadCoordinate(std::istringstream& isin) {
    double coordinate;
    isin >> coordinate;
    isin.ignore(10, ',');
    return coordinate;
  }
  Vec(const double x_, const double y_, const double z_)
      : x(x_), y(y_), z(z_) {}
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

  double Get(const Coordinate coordinate) const {
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
  bool WithinBounds() const {
    return x >= kRangeMin && x <= kRangeMax && y >= kRangeMin && y <= kRangeMax;
  }
};
struct Hailstone {
  const Vec pos, vel;

  static Vec ReadVec(std::istringstream& isin) {
    std::string vec_str;
    std::getline(isin, vec_str, '@');
    return Vec(vec_str);
  }
  Hailstone(std::istringstream&& isin)
      : pos(ReadVec(isin)), vel(ReadVec(isin)) {}
  Hailstone(const std::string& str) : Hailstone(std::istringstream(str)) {}

  std::string ToString() const {
    std::ostringstream sout;
    sout << pos << " @ " << vel;
    return sout.str();
  }
  friend std::ostream& operator<<(std::ostream& out, const Hailstone& h) {
    return out << h.ToString();
  }

  Vec AfterTime(const double t) const {
    return Vec{pos.x + vel.x * t, pos.y + vel.y * t, pos.z + vel.z * t};
  }
  bool CrossWithinBounds(const Hailstone& other) const {
    const double numerator_1 = other.vel.x * (other.pos.y - pos.y) -
                               other.vel.y * (other.pos.x - pos.x);
    const double numerator_2 =
        vel.x * (other.pos.y - pos.y) - vel.y * (other.pos.x - pos.x);
    const double denominator = vel.y * other.vel.x - vel.x * other.vel.y;
    DEBUG std::cout << "\t" << numerator_1 << " | " << numerator_2 << " | "
                    << denominator << "\n";
    if (denominator == 0) return false;

    const double t_1 = numerator_1 / denominator;
    const double t_2 = numerator_2 / denominator;
    DEBUG std::cout << "\t\tt_1: " << t_1 << " | t_2: " << t_2 << "\n";
    if (t_1 < 0 || t_2 < 0) return false;

    const Vec intersection = AfterTime(t_1);
    const bool within_bounds = intersection.WithinBounds();
    DEBUG std::cout << "\t\t\tintersection: " << intersection
                    << " | within_bounds: " << within_bounds << "\n";
    if (!within_bounds) return false;

    return true;
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

  int Solve() const {
    int ans = 0;
    for (int i = 0; i < hs.size(); ++i) {
      for (int j = i + 1; j < hs.size(); ++j) {
        const Hailstone &a = hs[i], b = hs[j];
        const bool crosses = a.CrossWithinBounds(b);
        DEBUG std::cout << i << " " << j
                        << " | a.CrossWithinBounds(b): " << crosses << "\n";
        if (!crosses) continue;
        ++ans;
      }
    }
    return ans;
  }
};

int main() {
  const Hailstones hailstones = Hailstones::Read();

  std::cout << hailstones;

  const int ans = hailstones.Solve();
  std::cout << "ans: " << ans << "\n";

  return 0;
}
