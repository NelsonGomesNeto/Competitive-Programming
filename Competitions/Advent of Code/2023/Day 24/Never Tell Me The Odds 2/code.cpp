#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
We want to find a hailstone (pos=u, vel=du) such that:
  for all hailstones (pos=v[i], vel=dv[i]):
    exists a t[i] that: u + du*t = v[i] + dv[i]*t

We can rearrage that as:
  (u - v[i]) = (dv[i] - du)*t, multiply by (du - dv[i])
  (u - v[i])*(du - dv[i]) = (dv[i] - du)*(du - dv[i])*t
    (dv[i] - du)*(du - dv[i]) = 0
    because it's the cross product of two parallel vectors
  (u - v[i])*(du - dv[i]) = 0
  u*du - u*dv[i] - v[i]*du + v[i]*dv[i] = 0
    u*du makes this not linear, but exists on the equations for all hailstones
Then, we have a system of equations:
  for i in hailstones:
    u*du - u*dv[i] - v[i]*du + v[i]*dv[i] = 0

If we pick three linearly indepenent hailstones (by vel)
  Why?
    They need to be linearly independent otherwise pairing them won't give
    us additional info about all dimensions.
    Note that they being linearly independent by vel implies that they're also
    by pos.
Then we can join them by pairs and transform the system in a real linear system
  eq[i]: u*du - u*dv[i] - v[i]*du + v[i]*dv[i] = 0
  eq[j]: u*du - u*dv[j] - v[j]*du + v[j]*dv[j] = 0, eq[i] - eq[j]
  u*(dv[j] - dv[i]) + du*(v[i] - v[j]) = v[j]*dv[j] - v[i]*dv[i]
  Then we do the same for the pair (i, k)

Finally, we can use Gauss Elimination to solve this system of equations :tada:
  What about the coordinates? Don't we only have 2 equations?
  Note that each equation has only vectors, each equation can be decomposed into
  3 equations, each for a different coordinate, for example:
    u*(dv[j] - dv[i]) + du*(v[i] - v[j]) = v[j]*dv[j] - v[i]*dv[i]
    but all using only the x coordinate

To avoid precision problems on Gauss Elimination:
  Consider using long double AND translating all positions closer to (0, 0, 0)
*/

const ldouble kEps = std::numeric_limits<ldouble>::epsilon();
int GaussMethod(std::vector<std::vector<ldouble>> a,
                std::vector<ldouble>& ans) {
  const int n = a.size(), m = a[0].size() - 1;

  std::vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row;
    for (int i = row; i < n; ++i) {
      if (std::abs(a[i][col]) <= std::abs(a[sel][col])) continue;
      sel = i;
    }

    if (std::abs(a[sel][col]) < kEps) continue;

    for (int j = col; j <= m; ++j) std::swap(a[sel][j], a[row][j]);
    where[col] = row;

    for (int i = 0; i < n; ++i) {
      if (i == row) continue;
      const ldouble c = a[i][col] / a[row][col];
      for (int j = col; j <= m; ++j) a[i][j] -= a[row][j] * c;
    }
    ++row;
  }

  ans.resize(m, 0);
  for (int i = 0; i < m; ++i) {
    if (where[i] == -1) continue;
    ans[i] = a[where[i]][m] / a[where[i]][i];
  }

  for (int i = 0; i < n; ++i) {
    ldouble sum = 0;
    for (int j = 0; j < m; ++j) sum += ans[j] * a[i][j];
    const ldouble rem = std::abs(sum - a[i][m]);
    if (rem > kEps) return 0;
  }

  for (int i = 0; i < m; ++i) {
    if (where[i] != -1) continue;
    return 2;
  }

  return 1;
}

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
const std::vector<Coordinate> kAllCoordinates = {X, Y, Z};

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
  Vec operator-(const Vec& other) const {
    return Vec{x - other.x, y - other.y, z - other.z};
  }
  Vec operator+(const Vec& other) const {
    return Vec{x + other.x, y + other.y, z + other.z};
  }
  Vec CrossProd(const Vec& other) const {
    const Vec &a = *this, &b = other;
    return Vec{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
               a.x * b.y - a.y * b.x};
  }
  std::vector<Vec> CrossProdOnVariable() const {
    const Vec& b = *this;
    return {Vec{0, b.z, -b.y}, Vec{-b.z, 0, b.x}, Vec{b.y, -b.x, 0}};
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

  ldouble Dist(const Vec& other) const {
    const ldouble xx = (x - other.x), yy = (y - other.y), zz = (z - other.z);
    return std::sqrt(xx * xx + yy * yy + zz * zz);
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
  ldouble MinDist(const Hailstone& other) const {
    lli t = 0;
    for (const Coordinate c : kAllCoordinates) {
      const lli denominator = vel.Get(c) - other.vel.Get(c);
      if (denominator == 0) continue;
      const lli numerator = other.pos.Get(c) - pos.Get(c);
      t = std::round((ldouble)numerator / denominator);
      break;
    }
    const Vec this_pos = AfterTime(t);
    const Vec other_pos = other.AfterTime(t);
    return this_pos.Dist(other_pos);
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

  ldouble SumMinDist(const Hailstone& bullet) const {
    ldouble res = 0;
    for (const Hailstone& h : hs) {
      res += bullet.MinDist(h);
    }
    return res;
  }
  std::vector<const Hailstone*> GetLinearIndependentHailstones() const {
    // Pick three hailstones with linear independent `vel`
    // If determinant is != 0 => vectors are linear independent
    // |x1 y1 z1|
    // |x2 y2 z2| = (x1*y2*z3 + y1*z2*x3 + z1*x2*y3)
    // |x3 y3 z3| - (y1*x2*z3 + x1*z2*y3 + z1*y2*x3)
    std::vector<int> chosen;
    for (int i = 0; i < hs.size() && chosen.empty(); ++i)
      for (int j = i + 1; j < hs.size() && chosen.empty(); ++j)
        for (int k = j + 1; k < hs.size() && chosen.empty(); ++k) {
          const lli x1 = hs[i].vel.x, y1 = hs[i].vel.y, z1 = hs[i].vel.z;
          const lli x2 = hs[j].vel.x, y2 = hs[j].vel.y, z2 = hs[j].vel.z;
          const lli x3 = hs[k].vel.x, y3 = hs[k].vel.y, z3 = hs[k].vel.z;
          const lli det = (x1 * y2 * z3 + y1 * z2 * x3 + z1 * x2 * y3) -
                          (y1 * x2 * z3 + x1 * z2 * y3 + z1 * y2 * x3);
          if (det == 0) continue;
          chosen.emplace_back(i);
          chosen.emplace_back(j);
          chosen.emplace_back(k);
        }
    DEBUG std::cout << "linear independent:\n";
    std::vector<const Hailstone*> v;
    for (const int i : chosen) {
      v.emplace_back(&hs[i]);
      DEBUG std::cout << "\t" << i << " | " << *v.back() << "\n";
    }
    return v;
  }
  // We'll model this with a system of linear equations.
  // We can represent that system with matrixes: Ax = b
  // Then we use the Gauss method to solve it \o/
  Hailstone FindBullet() const {
    Hailstone bullet;

    std::vector<const Hailstone*> v = GetLinearIndependentHailstones();
    // X means cross product
    // u X (dv[j] - dv[i]) + du X (v[i] - v[j]) = v[j] X dv[j] - v[i] X dv[i]
    // all variables will have their own constant
    // x^T = (u_x, u_y, u_z, du_x, du_y, du_z)
    /* A[0]^T = equation for x
       A[0]^T = |0                   | (u_x)
                |(dv[i]_z - dv[j]_z) | (u_y)
                |-(dv[i]_y - dv[j]_y)| (u_z)
                |0                   | (du_x)
                |(v[i]_z - v[j]_z)   | (du_y)
                |-(v[i]_y - v[j]_y)  | (du_z)
    */

    lli minimum_value = std::numeric_limits<lli>::max();
    for (const Hailstone* vi : v) {
      for (const Coordinate c : kAllCoordinates) {
        minimum_value = std::min(minimum_value, vi->pos.Get(c));
      }
    }

    std::vector<std::vector<ldouble>> a;
    for (int j = 1; j < v.size(); ++j) {
      const Hailstone &h1 = *v[0], &h2 = *v[j];
      DEBUG std::cout << "h1: " << h1 << "\n";
      DEBUG std::cout << "h2: " << h2 << "\n";
      // Translate closer to (0, 0, 0) not to waste precision.
      const Vec v1 = h1.pos - Vec{minimum_value, minimum_value, minimum_value},
                v2 = h2.pos - Vec{minimum_value, minimum_value, minimum_value};
      const Vec dv1 = h1.vel, dv2 = h2.vel;

      const Vec v = v1 - v2;
      DEBUG std::cout << "v: " << v << "\n";
      const std::vector<Vec> duv = v.CrossProdOnVariable();

      const Vec dv = dv2 - dv1;
      DEBUG std::cout << "dv: " << dv << "\n";
      const std::vector<Vec> udv = dv.CrossProdOnVariable();

      const Vec b = v2.CrossProd(dv2) - v1.CrossProd(dv1);
      DEBUG std::cout << "b: " << b << "\n";

      for (int equation = 0; equation < udv.size(); ++equation) {
        a.emplace_back();
        for (const Coordinate c : kAllCoordinates)
          a.back().push_back(udv[equation].Get(c));
        for (const Coordinate c : kAllCoordinates)
          a.back().push_back(duv[equation].Get(c));
        a.back().push_back(b.Get(kAllCoordinates[equation]));
      }
    }

    DEBUG {
      std::cout << "A concat b:\n";
      for (const std::vector<ldouble>& row : a) {
        std::cout << "\t";
        for (const ldouble e : row) {
          std::cout << e << " ";
        }
        std::cout << "\n";
      }
    }

    std::vector<ldouble> ans;
    const int gauss_method = GaussMethod(a, ans);
    std::cout << "GaussMethod: " << gauss_method << "\n";

    std::vector<Coordinate> coordinates{X, Y, Z, X, Y, Z};
    for (int i = 0; i < ans.size(); ++i) {
      if (i < 3) {
        bullet.pos.Set(coordinates[i], std::round(ans[i]) + minimum_value);
      } else {
        bullet.vel.Set(coordinates[i], std::round(ans[i]));
      }
    }

    return bullet;
  }

  lli Solve() const {
    lli ans = 0;

    const Hailstone bullet = FindBullet();
    std::cout << "bullet: " << bullet << "\n";
    std::cout << "dist: " << SumMinDist(bullet) << "\n";

    return bullet.pos.x + bullet.pos.y + bullet.pos.z;
  }
};

int main() {
  const Hailstones hailstones = Hailstones::Read();

  DEBUG std::cout << hailstones;

  const lli ans = hailstones.Solve();
  std::cout << "ans: " << ans << "\n";

  return 0;
}
