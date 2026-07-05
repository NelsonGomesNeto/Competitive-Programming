#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m, q;
  std::vector<std::tuple<int, int, char>> updates;
  std::vector<std::string> grid;
  bool Run() {
    if (!(std::cin >> n >> m >> q)) return false;
    grid.resize(n, std::string(m, '#'));
    updates.resize(q);
    for (auto& [i, j, c] : updates) {
      std::cin >> i >> j >> c;
      --i, --j;
    }

    for (const auto [hii, hij, c] : updates | std::views::reverse) {
      for (int i = hii; i >= 0; --i) {
        if (grid[i][hij] != '#') break;
        for (int j = hij; j >= 0; --j) {
          if (grid[i][j] != '#') break;
          grid[i][j] = c;
        }
      }
    }
    for (auto& line : grid) {
      for (auto& c : line)
        if (c == '#') c = 'A';
    }

    for (const auto& line : grid) std::println("{}", line);

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
