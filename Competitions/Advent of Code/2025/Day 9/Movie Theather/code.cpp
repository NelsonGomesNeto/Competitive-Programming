#include <bits/stdc++.h>
#define lli long long int

struct Pos {
  lli i, j;
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

struct Cinema {
  std::vector<Pos> red_tiles;

  friend std::istream& operator>>(std::istream& sin, Cinema& c) {
    c.red_tiles.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      c.red_tiles.emplace_back(line);
    }
    return sin;
  }

  lli BiggestRectangle() const {
    std::println("finding biggest rectangle");
    lli ans = 0;
    for (const auto& [i, a] : std::views::enumerate(red_tiles)) {
      for (const auto& [j, b] :
           std::views::enumerate(red_tiles) | std::views::drop(i + 1)) {
        const lli area = a.RectangleArea(b);
        std::println("\t{} x {} = {}", a, b, area);
        ans = std::max(ans, area);
      }
    }
    return ans;
  }
};
template <>
struct std::formatter<Cinema> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Cinema& c, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "{}",
        c.red_tiles | std::views::transform([](const Pos& pos) {
          return std::format("\t{}", pos);
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>());
  }
};

int main() {
  Cinema cinema;
  std::cin >> cinema;

  std::println("cinema:\n{}", cinema);

  const lli ans = cinema.BiggestRectangle();
  std::println("Ans: {}", ans);

  return 0;
}
