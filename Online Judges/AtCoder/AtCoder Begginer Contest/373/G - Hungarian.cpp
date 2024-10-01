#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
We can prove that if at least one solution exists, one of them will minimize:
  sum(dist(p_i, q_ri))

  Proof idea:
  If a pair of segments u, v intersects, then switching to any other pair of
  segments with those points will minimize the distance and reduce the number of
  intersections.

So, we can model this problem as a MinCostFlow and find the permutation that
minimizes the size of the segments.
LOVE IT.

Flow graph model (vertex -[cost, flow]> vertex):
source (0) -[0, 1]> p (1 : n) -[dist, 1]> q (1 + n : 2*n) -[0, 1]> sink (2*n +
1)

THIS SOLUTION USES HUNGARIAN INSTEAD BECAUSE IT'S FASTER SINCE THE FLOW IS
ALWAYS 1!!!!
*/

template <typename Cost>
struct Hungarian {
  int n;
  std::vector<std::vector<Cost>> costs;
  std::vector<Cost> u, v;
  std::vector<int> p, way;
  Cost inf;

  Hungarian() {}
  Hungarian(int n) : n(n), u(n + 1), v(n + 1), p(n + 1), way(n + 1) {
    inf = std::numeric_limits<Cost>::max();
    costs.resize(n, std::vector<Cost>(n, 0));
  }

  void AddEdge(int u, int v, Cost c) { costs[u][v] = c; }

  std::pair<Cost, std::vector<int>> Assignment() {
    for (int i = 1; i <= n; ++i) {
      p[0] = i;
      int j0 = 0;
      std::vector<Cost> minv(n + 1, inf);
      std::vector<int> used(n + 1, 0);
      do {
        used[j0] = true;
        int i0 = p[j0], j1 = -1;
        Cost delta = inf;
        for (int j = 1; j <= n; ++j) {
          if (used[j]) continue;
          Cost cur = costs[i0 - 1][j - 1] - u[i0] - v[j];
          if (cur < minv[j]) minv[j] = cur, way[j] = j0;
          if (minv[j] < delta) delta = minv[j], j1 = j;
        }
        for (int j = 0; j <= n; ++j) {
          if (used[j])
            u[p[j]] += delta, v[j] -= delta;
          else
            minv[j] -= delta;
        }
        j0 = j1;
      } while (p[j0] != 0);

      do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0);
    }
    std::vector<int> ans(n);
    for (int j = 1; j <= n; ++j) ans[p[j] - 1] = j - 1;
    return std::make_pair(-v[0], ans);
  }
};

struct Point {
  int x, y;
  ldouble Dist(const Point& other) const {
    return std::sqrt((x - other.x) * (x - other.x) +
                     (y - other.y) * (y - other.y));
  }

  bool ccw(const Point& B, const Point& C) const {
    return (C.y - y) * (B.x - x) > (B.y - y) * (C.x - x);
  }

  friend std::ostream& operator<<(std::ostream& out, const Point& p) {
    return out << "(" << p.x << ", " << p.y << ")";
  }
};

struct Segment {
  Point p1, p2;
  bool InterceptsSegment(const Point& q1, const Point& q2) {
    return p1.ccw(q1, q2) != p2.ccw(q1, q2) && p1.ccw(p2, q1) != p1.ccw(p2, q2);
  }
  bool InterceptsSegment(const Segment& s) {
    return InterceptsSegment(s.p1, s.p2);
  }
};

struct TestCase {
  int n;
  std::vector<Point> a, b;
  std::vector<int> ans;

  bool Solve() {
    if (!(std::cin >> n)) return false;

    a.resize(n), b.resize(n);
    for (Point& p : a) std::cin >> p.x >> p.y;
    for (Point& p : b) std::cin >> p.x >> p.y;

    Hungarian<ldouble> hungarian(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        hungarian.AddEdge(i, j, a[i].Dist(b[j]));
      }
    }

    const auto [min_cost, assignment] = hungarian.Assignment();

    // Try to find intersections.
    bool has_intersection = false;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (!Segment{a[i], b[assignment[i]]}.InterceptsSegment(
                a[j], b[assignment[j]]))
          continue;
        has_intersection = true;
      }
    }

    if (has_intersection) {
      std::cout << "-1\n";
      return true;
    }

    ans = assignment;

    for (int i = 0; i < n; ++i) {
      if (i) std::cout << " ";
      std::cout << (ans[i] + 1);
    }
    std::cout << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  do {
    test_case = TestCase{};
  } while (test_case.Solve());
  return 0;
}