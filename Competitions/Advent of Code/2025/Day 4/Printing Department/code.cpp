#include <bits/stdc++.h>

const int kDirCount = 8;
const int kDi[kDirCount] = {1, 1, 1, 0, 0, -1, -1, -1};
const int kDj[kDirCount] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Diagram {
  int n, m;
  std::vector<std::string> grid;
  std::vector<std::string> painted_grid;

  friend std::istream& operator>>(std::istream& sin, Diagram& d) {
    d.grid.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      d.grid.push_back(line);
    }
    d.n = d.grid.size();
    d.m = d.grid[0].size();
    d.painted_grid = d.grid;
    return sin;
  }

  int AccessibleCount() {
    int accessible_count = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (grid[i][j] != '@') continue;

        int adjacent_count = 0;
        for (int d = 0; d < kDirCount; ++d) {
          const int ni = i + kDi[d], nj = j + kDj[d];
          if (ni < 0 || ni >= n || nj < 0 || nj >= m || grid[ni][nj] != '@')
            continue;
          ++adjacent_count;
        }
        if (adjacent_count >= 4) continue;
        ++accessible_count;
        painted_grid[i][j] = 'x';
      }
    }
    return accessible_count;
  }
};
template <>
struct std::formatter<Diagram> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Diagram& d, FormatContext& ctx) const {
    std::format_to(ctx.out(), "\toriginal grid:\n");
    for (int i = 0; i < d.n; ++i) {
      std::format_to(ctx.out(), "{}", d.grid[i]);
      if (i + 1 != d.n) std::format_to(ctx.out(), "\n");
    }
    std::format_to(ctx.out(), "\n\tpainted grid:\n");
    for (int i = 0; i < d.n; ++i) {
      std::format_to(ctx.out(), "{}", d.painted_grid[i]);
      if (i + 1 != d.n) std::format_to(ctx.out(), "\n");
    }
    return ctx.out();
  }
};

int main() {
  Diagram diagram;
  std::cin >> diagram;

  const int ans = diagram.AccessibleCount();
  std::println("diagram:\n{}", diagram);
  std::println("Ans: {}", ans);

  return 0;
}
