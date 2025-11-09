#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const int kSteps = 100;

int BoundByLimit(const int x, const int limit) {
  return ((x % limit) + limit) % limit;
}

enum class Quadrant { Q1, Q2, Q3, Q4 };
const std::vector<Quadrant> kAllQuadrants = {Quadrant::Q1, Quadrant::Q2,
                                             Quadrant::Q3, Quadrant::Q4};

struct Vec {
  int i, j;
  Vec() {}
  Vec(const int i, const int j) : i(i), j(j) {}
  Vec Add(const Vec& other) const { return Vec(i + other.i, j + other.j); }
  Vec Mult(const int k) const { return Vec(i * k, j * k); }
  void BoundByLimits(const int n, const int m) {
    i = BoundByLimit(i, n), j = BoundByLimit(j, m);
  }
  friend std::istream& operator>>(std::istream& in, Vec& v) {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '=');
    in >> v.j;
    in.ignore(1);
    in >> v.i;
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const Vec& v) {
    return out << "(" << v.i << ", " << v.j << ")";
  }
};
struct Robot {
  Vec p, v;
  Robot(const std::string& line) {
    std::istringstream sin(line);
    sin >> p >> v;
  }
  void Walk(const int steps, const int n, const int m) {
    p = p.Add(v.Mult(steps));
    p.BoundByLimits(n, m);
  }
  friend std::ostream& operator<<(std::ostream& out, const Robot& r) {
    return out << "p=" << r.p << " | v=" << r.v;
  }
};
struct Problem {
  int n, m;
  std::vector<Robot> robots;
  std::vector<std::vector<int>> map;

  void PrintMap() {
    for (auto& line : map) std::ranges::fill(line, 0);
    for (const auto& r : robots) ++map[r.p.i][r.p.j];

    for (const auto& line : map) {
      for (const int cnt : line) {
        if (cnt)
          std::cout << cnt;
        else
          std::cout << '.';
      }
      std::cout << "\n";
    }
  }

  void Solve() {
    std::cin >> n >> m;
    std::cin.ignore(1);
    map.resize(n, std::vector<int>(m, 0));

    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      robots.emplace_back(line);
    }
    std::cout << n << " " << m << " | robots: " << (int)robots.size() << "\n";

    DEBUG {
      for (const auto& r : robots) {
        std::cout << r << "\n";
      }
      PrintMap();
      std::cout << "-----------\n";
    }

    const Vec mid(n / 2, m / 2);
    std::vector<int> cnt_by_quadrant(4, 0);
    for (auto& r : robots) {
      r.Walk(kSteps, n, m);
      for (const auto& q : kAllQuadrants) {
        const bool on_quadrant = [&]() -> bool {
          switch (q) {
            case Quadrant::Q1:
              return r.p.i < mid.i && r.p.j > mid.j;
            case Quadrant::Q2:
              return r.p.i < mid.i && r.p.j < mid.j;
            case Quadrant::Q3:
              return r.p.i > mid.i && r.p.j < mid.j;
            case Quadrant::Q4:
            default:
              return r.p.i > mid.i && r.p.j > mid.j;
          }
        }();
        if (!on_quadrant) continue;
        ++cnt_by_quadrant[(int)q];
      }
    }
    PrintMap();

    int ans = 1;
    for (const int q : cnt_by_quadrant) ans *= q;
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
