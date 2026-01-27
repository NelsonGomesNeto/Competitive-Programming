#include <bits/stdc++.h>
#ifdef DEB
#define DEBUG if (1)
#else
#define DEBUG if (0)
#endif
#define lli long long int

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

  // Sends a bean through `S` and returns a pair with the number of splits and
  // the number of timelines.
  std::vector<std::vector<lli>> timelines_memo;
  int split_count;
  std::pair<int, lli> SendBean() {
    split_count = 0;
    timelines_memo.resize(n, std::vector<lli>(m, -1));
    const lli timeline_count = SendBean(start_pos.i, start_pos.j);
    return {split_count, timeline_count};
  }
  // Recursively sends a bean through `S` and returns the number of timelines
  // while updating the number of splits at `split_count`.
  lli SendBean(const int i, const int j) {
    if (i == n) return 1;
    DEBUG {
      std::println("{} {} | {} | {}", i, j, grid[i][j], timelines_memo[i][j]);
      std::fflush(stdout);
    }

    lli& timeline_count = timelines_memo[i][j];
    if (timeline_count != -1) {
      return timeline_count;
    }
    timeline_count = 0;

    if (grid[i][j] == '.' || grid[i][j] == 'S') {
      if (grid[i][j] == '.') grid[i][j] = '|';
      timeline_count += SendBean(i + 1, j);
      return timeline_count;
    }

    assert(grid[i][j] == '^');
    ++split_count;
    if (j - 1 >= 0) {
      timeline_count += SendBean(i, j - 1);
    }
    if (j + 1 < m) {
      timeline_count += SendBean(i, j + 1);
    }
    return timeline_count;
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

  const auto [split_count, timeline_count] = tachyon_manifold.SendBean();
  std::println("tachyon_manifold:\n{}", tachyon_manifold);
  std::println("split_count: {} | timeline_count: {}", split_count,
               timeline_count);
  std::println("Ans: {}", timeline_count);

  return 0;
}
