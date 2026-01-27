#include <bits/stdc++.h>

struct Pos {
  int i, j;
};
struct TachyonManifold {
  int n, m;
  Pos start_pos;
  std::vector<std::string> grid;

  friend std::istream& operator>>(std::istream& sin, TachyonManifold& t) {
    t.grid.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      t.grid.push_back(line);
    }
    t.start_pos = {-1, -1};
    t.n = t.grid.size(), t.m = t.grid[0].size();
    for (const auto& [i, line] : std::views::enumerate(t.grid)) {
      for (const auto& [j, c] : std::views::enumerate(line)) {
        if (c != 'S') continue;
        t.start_pos = {(int)i, (int)j};
        break;
      }
      if (t.start_pos.i != -1) break;
    }
    return sin;
  }

  // Sends a bean through `S` and returns the number of splits.
  int SendBean() {
    int split_count = 0;
    std::vector<Pos> queue;
    queue.reserve(n * m);
    queue.push_back(start_pos);
    for (int qi = 0; qi < (int)queue.size(); ++qi) {
      const auto& [i, j] = queue[qi];
      if (grid[i][j] == '|') continue;
      if (grid[i][j] == '.') {
        grid[i][j] = '|';
      }

      if (i + 1 == n) continue;
      if (grid[i + 1][j] == '.') {
        queue.emplace_back(i + 1, j);
        continue;
      }

      assert(grid[i + 1][j] == '^');
      ++split_count;
      if (j - 1 >= 0) queue.emplace_back(i + 1, j - 1);
      if (j + 1 < m) queue.emplace_back(i + 1, j + 1);
    }
    return split_count;
  }
};
template <>
struct std::formatter<TachyonManifold> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const TachyonManifold& t, FormatContext& ctx) const {
    const auto joined_view = t.grid | std::views::join_with('\n');
    return std::format_to(ctx.out(), "{}",
                          std::string(joined_view.begin(), joined_view.end()));
  }
};

int main() {
  TachyonManifold tachyon_manifold;
  std::cin >> tachyon_manifold;

  std::println("tachyon_manifold:\n{}", tachyon_manifold);

  const int ans = tachyon_manifold.SendBean();
  std::println("tachyon_manifold:\n{}", tachyon_manifold);
  std::println("Ans: {}", ans);

  return 0;
}
