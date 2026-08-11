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

  int WrappingPaper() const {
    return 2 * x * y + 2 * x * z + 2 * y * z + std::min({x * y, x * z, y * z});
  }
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

  int TotalWrappingPaper() const {
    int paper = 0;
    for (const auto& p : presents) {
      const int to_add = p.WrappingPaper();
      std::println("\t{} -> {}", p, to_add);
      paper += to_add;
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

  const int ans = order.TotalWrappingPaper();
  std::println("ans: {}", ans);

  return 0;
}