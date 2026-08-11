#include <bits/stdc++.h>

const std::array<std::pair<int, int>, 256> kDeltaByDir = []() {
  std::array<std::pair<int, int>, 256> delta_by_dir;
  delta_by_dir['^'] = {-1, 0};
  delta_by_dir['>'] = {0, 1};
  delta_by_dir['v'] = {1, 0};
  delta_by_dir['<'] = {0, -1};
  return delta_by_dir;
}();

struct Map {
  std::string instructions;
  friend std::istream& operator>>(std::istream& sin, Map& m) {
    sin >> m.instructions;
    return sin;
  }

  int DeliveredPresents() const {
    std::set<std::pair<int, int>> visited;
    int i = 0, j = 0;
    visited.emplace(i, j);
    for (const char d : instructions | std::views::stride(2)) {
      const auto [di, dj] = kDeltaByDir[d];
      i += di, j += dj;
      visited.emplace(i, j);
    }
    i = 0, j = 0;
    for (const char d :
         instructions | std::views::drop(1) | std::views::stride(2)) {
      const auto [di, dj] = kDeltaByDir[d];
      i += di, j += dj;
      visited.emplace(i, j);
    }
    return visited.size();
  }

  void DrawPath() const {
    std::map<std::pair<int, int>, int> visited = [&]() {
      std::map<std::pair<int, int>, int> visited;
      int i = 0, j = 0;
      visited.emplace(std::make_pair(i, j), 0);
      for (const auto [k, d] :
           instructions | std::views::stride(2) | std::views::enumerate) {
        const auto [di, dj] = kDeltaByDir[d];
        i += di, j += dj;
        visited.emplace(std::make_pair(i, j), k + 1);
        // visited[std::make_pair(i, j)] = k + 1;
      }
      i = 0, j = 0;
      for (const auto [k, d] : instructions | std::views::drop(1) |
                                   std::views::stride(2) |
                                   std::views::enumerate) {
        const auto [di, dj] = kDeltaByDir[d];
        i += di, j += dj;
        visited.emplace(std::make_pair(i, j), k + 1);
        // visited[std::make_pair(i, j)] = k + 1;
      }
      return visited;
    }();
    int min_i = std::numeric_limits<int>::max(),
        min_j = std::numeric_limits<int>::max(),
        max_i = std::numeric_limits<int>::min(),
        max_j = std::numeric_limits<int>::min();
    for (const auto [ij, k] : visited) {
      const auto [i, j] = ij;
      min_i = std::min(min_i, i), max_i = std::max(max_i, i);
      min_j = std::min(min_j, j), max_j = std::max(max_j, j);
    }
    visited = [&]() {
      std::map<std::pair<int, int>, int> new_visited;
      for (const auto [ij, k] : visited) {
        const auto [i, j] = ij;
        new_visited.emplace(std::make_pair(i - min_i, j - min_j), k);
      }
      return new_visited;
    }();
    max_i -= min_i, max_j -= min_j;
    min_i -= min_i, min_j -= min_j;
    std::println("bounding_box: {} {} | {} {}", min_i, min_j, max_i, max_j);
    std::vector<std::vector<int>> grid(max_i + 1,
                                       std::vector<int>(max_j + 1, -1));
    for (const auto [ij, k] : visited) {
      const auto [i, j] = ij;
      grid[i][j] = k;
    }
    std::println("path:");
    for (const auto& line : grid) {
      std::println("{}", line | std::views::transform([&](const int a) {
                           if (a == -1)
                             return '.';
                           else
                             return (char)('0' + (a % 10));
                         }) | std::ranges::to<std::string>());
    }
    std::ofstream ofs("image.ppm", std::ios_base::out | std::ios_base::binary);
    const std::vector<std::vector<int>> kRainbow = {
        {255, 0, 0},     // 0 red
        {255, 127, 0},   // 1 orange
        {255, 255, 0},   // 2 yellow
        {0, 128, 0},     // 3 green
        {0, 0, 255},     // 4 blue
        {75, 0, 130},    // 5 indigo
        {138, 43, 226},  // 6 violeta
    };
    const int kMaxSteps = ((int)kRainbow.size() - 1) * 1500 >> 1;
    const int bl = (kMaxSteps / (kRainbow.size() - 1)) +
                   (kMaxSteps % (kRainbow.size() - 1) != 0);
    ofs << "P6\n" << grid[0].size() << " " << grid.size() << "\n255\n";
    for (const auto& line : grid) {
      for (const int c : line) {
        if (c == -1) {
          // ofs << (char)255 << (char)255 << (char)255;
          ofs << (char)0 << (char)0 << (char)0;
        } else if (c == 0) {
          ofs << (char)255 << (char)0 << (char)0;
        } else {
          const int a = c % kMaxSteps;
          const int i = a / bl;
          const int t = a % bl;
          if (i + 1 == kRainbow.size()) {
            std::println("{} {} {}", a, bl, i);
            assert(false);
          }
          for (const auto [prv, nxt] :
               std::views::zip(kRainbow[i], kRainbow[i + 1])) {
            const int delta = nxt - prv;
            const double p = (double)t / bl;
            ofs << (uint8_t)(prv + p * delta);
          }
        }
      }
    }
  }
};
template <>
struct std::formatter<Map> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Map& m, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}", m.instructions);
  }
};

int main() {
  while (true) {
    Map m;
    if (!(std::cin >> m)) break;
    std::println("map:\n\t{}", m);

    m.DrawPath();

    const int ans = m.DeliveredPresents();
    std::println("ans: {}", ans);

    std::println("{}", std::string(80, '-'));
  }
  return 0;
}
