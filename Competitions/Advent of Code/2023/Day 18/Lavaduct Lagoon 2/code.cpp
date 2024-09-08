#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

enum Dir { R, D, L, U, X };
const int dy[5] = {0, -1, 0, 1, 0};
const int dx[5] = {1, 0, -1, 0, 0};
std::map<char, Dir> dir_by_name = {
    {'R', Dir::R}, {'D', Dir::D}, {'L', Dir::L}, {'U', Dir::U}, {'X', Dir::X}};
const char dir_name[5] = {'R', 'D', 'L', 'U', 'X'};
bool IsVerticalDir(const Dir dir) { return dir == Dir::U || dir == Dir::D; }

struct Dig {
  Dir dir;
  int steps;

  Dig(const std::string& d) {
    std::istringstream sin(d);

    char old_dir_name;
    int old_steps;
    sin >> old_dir_name >> old_steps;

    sin.ignore(3) >> std::hex >> steps;
    dir = Dir(steps & 0b11);
    steps >>= 4;

    std::cout << dir_name[dir] << " " << steps << "\n";
  }
};
struct Point {
  int x, y;
};
struct DigPlan {
  std::vector<Dig> digs;
  std::vector<Point> points;
  int n, m;

  DigPlan() {}
  DigPlan(const std::vector<std::string>& ds) {
    for (const auto& d : ds) digs.emplace_back(d);
    ExecutePlan();
  }

  void ExecutePlan() {
    int x = 0, y = 0;
    for (const auto& dig : digs) {
      const int nx = x + dig.steps * dx[dig.dir],
                ny = y + dig.steps * dy[dig.dir];
      x = nx, y = ny;
      points.emplace_back(x, y);
    }

    // Crazy thing
    points.push_back(points[0]);
  }

  void PrintResult() {
    for (const auto p : points) {
      std::cout << "{" << p.x << ", " << p.y << "},\n";
    }
  }

  lli CubicMeters() {
    lli area = 0, perimeter = 0;
    for (int i = 1; i < points.size(); ++i) {
      const lli x0 = points[i - 1].x, y0 = points[i - 1].y;
      const lli x1 = points[i].x, y1 = points[i].y;
      // Shoelace formula
      area += (x0 * y1 - x1 * y0);
      perimeter += llabs(x1 - x0) + llabs(y1 - y0);
    }
    area >>= 1LL;
    area = llabs(area);
    perimeter >>= 1LL;
    lli ans = area + perimeter + 1;
    return ans;
  }
};

int main() {
  std::vector<std::string> ds;
  for (std::string line; std::getline(std::cin, line);) {
    ds.push_back(line);
  }
  DigPlan dig_plan(ds);

  dig_plan.PrintResult();
  lli ans = dig_plan.CubicMeters();
  std::cout << ans << "\n";

  return 0;
}
