#include <bits/stdc++.h>

const int kDirCount = 8;
const int kDi[kDirCount] = {1, 1, 1, 0, 0, -1, -1, -1};
const int kDj[kDirCount] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Diagram {
  int n, m;
  std::vector<std::string> grid;

  friend std::istream& operator>>(std::istream& sin, Diagram& d) {
    d.grid.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      d.grid.push_back(line);
    }
    d.n = d.grid.size();
    d.m = d.grid[0].size();
    return sin;
  }

  std::vector<std::string> to_remove;
  int RemoveAccessible() {
    to_remove = grid;
    int removed_count = 0;
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

        to_remove[i][j] = 'x';
        ++removed_count;
      }
    }
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (to_remove[i][j] != 'x') continue;
        grid[i][j] = '.';
      }

    std::println("\tremoved_count: {}", removed_count);
    for (const auto& r : to_remove) std::println("{}", r);
    return removed_count;
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
    return ctx.out();
  }
};

int main() {
  Diagram diagram;
  std::cin >> diagram;
  std::println("diagram:\n{}", diagram);

  int ans = 0;
  while (true) {
    const int removed = diagram.RemoveAccessible();
    if (removed == 0) break;
    ans += removed;
  }
  std::println("Ans: {}", ans);

  return 0;
}
