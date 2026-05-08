#include <bits/stdc++.h>
#ifdef DEB
#define DEBUG if (1)
#else
#define DEBUG if (0)
#endif
#define lli long long int

const int kDirCount = 4;
const int kDi[kDirCount] = {0, 1, -1, 0};
const int kDj[kDirCount] = {1, 0, 0, -1};

struct Pos {
  lli i, j;
  Pos() {}
  Pos(const lli i_, const lli j_) : i(i_), j(j_) {}
  Pos(std::istream&& sin)
      : i([&]() {
          lli a;
          sin >> a;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ',');
          return a;
        }()),
        j([&]() {
          lli a;
          sin >> a;
          return a;
        }()) {}
  Pos(const std::string& pos_str) : Pos(std::istringstream(pos_str)) {}

  lli RectangleArea(const Pos& o) const {
    const lli a = std::abs(i - o.i) + 1, b = std::abs(j - o.j) + 1;
    return a * b;
  }
};
template <>
struct std::formatter<Pos> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Pos& p, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "({}, {})", p.i, p.j);
  }
};

template <class T>
void MakeUnique(std::vector<T>& a) {
  std::ranges::sort(a);
  a.resize(std::distance(a.begin(), std::unique(a.begin(), a.end())));
}

struct Cinema {
  std::vector<Pos> red_tiles;
  std::vector<lli> alli, allj;
  std::vector<std::string> grid;
  std::vector<std::vector<lli>> acc;

  friend std::istream& operator>>(std::istream& sin, Cinema& c) {
    c.red_tiles.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      c.red_tiles.emplace_back(line);
    }
    c.BuildCompressedGrid();
    return sin;
  }

  int GetI(const Pos& a) const {
    return (int)(std::ranges::lower_bound(alli, a.i) - alli.begin());
  }
  int GetI(const int i) const {
    return (int)(std::ranges::lower_bound(alli, i) - alli.begin());
  }
  int GetJ(const Pos& a) const {
    return (int)(std::ranges::lower_bound(allj, a.j) - allj.begin());
  }
  int GetJ(const int j) const {
    return (int)(std::ranges::lower_bound(allj, j) - allj.begin());
  }
  void MakeGreenLine(const Pos& a, const Pos& b) {
    for (int i = std::min(GetI(a), GetI(b)), lasti = std::max(GetI(a), GetI(b));
         i <= lasti; ++i) {
      for (int j = std::min(GetJ(a), GetJ(b)),
               lastj = std::max(GetJ(a), GetJ(b));
           j <= lastj; ++j) {
        if (grid[i][j] == '#') continue;
        grid[i][j] = 'X';
      }
    }
  }
  void FloodFill(const int si, const int sj) {
    std::queue<std::pair<int, int>> q;
    q.emplace(si, sj);
    while (!q.empty()) {
      const auto [i, j] = q.front();
      q.pop();
      if (grid[i][j] != '.') continue;
      grid[i][j] = 'x';
      for (int d = 0; d < kDirCount; ++d) {
        const int ni = i + kDi[d], nj = j + kDj[d];
        if (ni < 0 || ni >= (int)alli.size() || nj < 0 ||
            nj >= (int)allj.size() || grid[ni][nj] != '.')
          continue;
        q.emplace(ni, nj);
      }
    }
  }
  void BuildCompressedGrid() {
    for (const auto& a : red_tiles) {
      alli.push_back(a.i);
      allj.push_back(a.j);
    }
    MakeUnique(alli), MakeUnique(allj);
    grid.resize(alli.size(), std::string(allj.size(), '.'));

    for (const auto& a : red_tiles) {
      grid[GetI(a)][GetJ(a)] = '#';
    }
    for (const auto& [i, a] :
         red_tiles | std::views::enumerate | std::views::drop(1)) {
      const auto& b = red_tiles[i - 1];
      MakeGreenLine(a, b);
    }
    MakeGreenLine(red_tiles[0], red_tiles.back());

    // Is there a better way to know where to start the floodfill?
    for (int i = 0, endi = (int)alli.size(), done = false; i < endi && !done;
         ++i) {
      for (int j = 0, endj = 1; j < endj; ++j) {
        if (grid[i][j] == 'X' && grid[i][j + 1] == '.') {
          FloodFill(i, j + 1);
          done = true;
          break;
        }
      }
    }

    acc.resize(grid.size() + 1, std::vector<lli>(grid.size() + 1, 0));
    for (const auto [i, line] : grid | std::views::enumerate) {
      for (const auto [j, c] : line | std::views::enumerate) {
        acc[i + 1][j + 1] =
            acc[i][j + 1] + acc[i + 1][j] - acc[i][j] + (c != '.');
      }
    }
  }

  // O(n*m) check
  bool IsRectangleSafe(const Pos& a, const Pos& b) const {
    const Pos up_left_corner{std::min(a.i, b.i), std::min(a.j, b.j)},
        down_right_corner{std::max(a.i, b.i), std::max(a.j, b.j)};
    for (int i = GetI(up_left_corner), lasti = GetI(down_right_corner);
         i <= lasti; ++i) {
      for (int j = GetJ(up_left_corner), lastj = GetJ(down_right_corner);
           j <= lastj; ++j) {
        if (grid[i][j] == '.') return false;
      }
    }
    return true;
  }

  lli GetValidCellsCount(const int loi, const int loj, const int hii,
                         const int hij) const {
    return acc[hii + 1][hij + 1] - acc[loi][hij + 1] - acc[hii + 1][loj] +
           acc[loi][loj];
  }
  // O(1) check using accumulated sums \o/
  bool FastIsRectanbleSafe(const Pos& a, const Pos& b) const {
    const int loi = GetI(std::min(a.i, b.i)), loj = GetJ(std::min(a.j, b.j)),
              hii = GetI(std::max(a.i, b.i)), hij = GetJ(std::max(a.j, b.j));
    const lli area = (lli)(hii - loi + 1) * (hij - loj + 1);
    const lli valid_cells = GetValidCellsCount(loi, loj, hii, hij);
    return area == valid_cells;
  }

  lli BiggestRectangle() const {
    std::println("finding biggest rectangle");
    lli ans = 0;
    for (const auto& [i, a] : std::views::enumerate(red_tiles)) {
      for (const auto& [j, b] :
           std::views::enumerate(red_tiles) | std::views::drop(i + 1)) {
        if (!FastIsRectanbleSafe(a, b)) continue;
        const lli area = a.RectangleArea(b);
        std::println("\t{} {} | {} x {} = {}", Pos{GetI(a), GetJ(a)},
                     Pos{GetI(b), GetJ(b)}, a, b, area);
        ans = std::max(ans, area);
      }
    }
    return ans;
  }

  void PrintImage() const {
    std::array<std::tuple<int, int, int>, 256> color_map;
    color_map['.'] = {0, 0, 0};
    color_map['#'] = {255, 0, 0};
    color_map['X'] = {255, 100, 0};
    color_map['x'] = {0, 255, 0};
    std::ofstream out("image.ppm", std::ofstream::binary);
    std::println(out, "P6\n{} {}\n255", grid[0].size(), grid.size());
    for (const auto& line : grid) {
      for (const auto c : line) {
        const auto [r, g, b] = color_map[c];
        std::print(out, "{}{}{}", (char)r, (char)g, (char)b);
      }
    }
  }
};
template <>
struct std::formatter<Cinema> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Cinema& c, FormatContext& ctx) const {
    std::format_to(ctx.out(), "\tred_tiles:\n{}",
                   c.red_tiles | std::views::transform([](const Pos& pos) {
                     return std::format("\t{}", pos);
                   }) | std::views::join_with('\n') |
                       std::ranges::to<std::string>());
    return std::format_to(
        ctx.out(), "\ngrid:\n{}",
        c.grid | std::views::join_with('\n') | std::ranges::to<std::string>());
  }
};

int main() {
  Cinema cinema;
  std::cin >> cinema;

  std::println("cinema:\n{}", cinema);

  const lli ans = cinema.BiggestRectangle();
  std::println("Ans: {}", ans);

  cinema.PrintImage();

  return 0;
}
