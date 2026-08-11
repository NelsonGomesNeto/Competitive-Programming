#include <bits/stdc++.h>

struct Present {
  int x, y, z;
  friend std::istream& operator>>(std::istream& sin, Present& p) {
    sin >> p.x;
    sin.ignore(1);
    sin >> p.y;
    sin.ignore(1);
    sin >> p.z;
    return sin;
  }

  int RibbonWrap() const { return 2 * std::min({x + y, x + z, y + z}); }
  int RibbonBow() const { return x * y * z; }
};
template <>
struct std::formatter<Present> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Present& p, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}x{}x{}", p.x, p.y, p.z);
  }
};

struct Order {
  std::vector<Present> presents;
  friend std::istream& operator>>(std::istream& sin, Order& o) {
    while (true) {
      Present p;
      if (!(sin >> p)) break;
      o.presents.push_back(p);
    }
    return sin;
  }

  int TotalRibbon() const {
    int paper = 0;
    for (const auto& p : presents) {
      const int ribbon_wrap = p.RibbonWrap();
      const int ribbon_bow = p.RibbonBow();
      std::println("\t{} -> {} {}", p, ribbon_wrap, ribbon_bow);
      paper += ribbon_wrap + ribbon_bow;
    }
    return paper;
  }
};
template <>
struct std::formatter<Order> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Order& o, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "{}",
        o.presents | std::views::transform([](const Present& p) {
          return std::format("{}", p);
        }) | std::views::join_with(std::string_view("\n\t")) |
            std::ranges::to<std::string>());
  }
};

int main() {
  Order order;
  std::cin >> order;

  std::println("order:\n\t{}", order);

  const int ans = order.TotalRibbon();
  std::println("ans: {}", ans);

  return 0;
}