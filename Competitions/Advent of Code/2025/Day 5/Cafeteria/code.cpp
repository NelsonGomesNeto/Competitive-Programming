#include <bits/stdc++.h>
#define lli long long int

struct Range {
  const lli start, end;
  Range(std::istream&& sin)
      : start([&]() {
          lli s;
          sin >> s;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), '-');
          return s;
        }()),
        end([&]() {
          lli e;
          sin >> e;
          return e;
        }()) {}
  Range(const std::string& range_str) : Range(std::istringstream(range_str)) {}
};
template <>
struct std::formatter<Range> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Range& r, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}-{}", r.start, r.end);
  }
};

struct Cafeteria {
  std::vector<Range> fresh_ranges;
  std::vector<lli> ingredients;

  friend std::istream& operator>>(std::istream& sin, Cafeteria& c) {
    c.fresh_ranges.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      c.fresh_ranges.emplace_back(line);
    }
    for (lli i = -1; sin >> i && i != -1; i = -1) {
      c.ingredients.push_back(i);
    }
    return sin;
  }

  int FreshIngredientsCount() const {
    int count = 0;
    for (const lli i : ingredients) {
      const bool is_fresh = [&]() {
        for (const auto& r : fresh_ranges) {
          if (i >= r.start && i <= r.end) return true;
        }
        return false;
      }();

      if (is_fresh) ++count;
    }
    return count;
  }
};
template <>
struct std::formatter<Cafeteria> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Cafeteria& c, FormatContext& ctx) const {
    std::format_to(ctx.out(), "\tranges:\n");
    for (int i = 0; i < c.fresh_ranges.size(); ++i) {
      std::format_to(ctx.out(), "{}", c.fresh_ranges[i]);
      if (i + 1 != c.fresh_ranges.size()) std::format_to(ctx.out(), "\n");
    }
    std::format_to(ctx.out(), "\n\tingredients:\n");
    for (int i = 0; i < c.ingredients.size(); ++i) {
      std::format_to(ctx.out(), "{}", c.ingredients[i]);
      if (i + 1 != c.ingredients.size()) std::format_to(ctx.out(), "\n");
    }
    return ctx.out();
  }
};

int main() {
  Cafeteria cafeteria;
  std::cin >> cafeteria;

  std::println("cafeteria:\n{}", cafeteria);

  const int ans = cafeteria.FreshIngredientsCount();
  std::println("Ans: {}", ans);

  return 0;
}
