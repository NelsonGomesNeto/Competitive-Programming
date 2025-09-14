#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  struct Point {
    int x, y;
  };
  std::vector<Point> people;
  bool Run() {
    if (!(std::cin >> n)) return false;
    people.resize(n);
    for (auto& [x, y] : people) {
      std::cin >> x >> y;
    }

    int min_x = 1e9 + 1, max_x = -1, min_y = 1e9 + 1, max_y = -1;
    for (const auto [x, y] : people) {
      min_x = std::min(min_x, x);
      max_x = std::max(max_x, x);
      min_y = std::min(min_y, y);
      max_y = std::max(max_y, y);
    }
    int mid_x = std::round(((double)(max_x + min_x)) / 2);
    int mid_y = std::round(((double)(max_y + min_y)) / 2);
    DEBUG std::cout << "\t" << mid_x << " " << mid_y << "\n";
    int ans = 0;
    for (const auto [x, y] : people) {
      const int dx = std::abs(mid_x - x), dy = std::abs(mid_y - y);
      const int min_d = std::min(dx, dy), max_d = std::max(dx, dy);
      const int move = min_d + (max_d - min_d);
      ans = std::max(ans, move);
    }
    std::cout << ans << "\n";

    return true;
  }
};

int main() {
  while (true) {
    TestCase test_case{};
    if (!test_case.Run()) break;
  }
  return 0;
}