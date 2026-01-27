#include <bits/stdc++.h>
#define lli long long int

struct Range {
  lli start, end;
  Range(std::istream&& sin) {
    sin >> start;
    sin.ignore(std::numeric_limits<std::streamsize>::max(), '-');
    sin >> end;
  }
  Range(const std::string& range) : Range(std::istringstream(range)) {}
};
template <>
struct std::formatter<Range> {
  constexpr auto parse(std::format_parse_context& ctx) {
    auto it = ctx.begin();
    return it;
  }
  template <class FormatContext>
  auto format(const Range& r, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}-{}", r.start, r.end);
  }
};

struct Store {
  std::vector<Range> ranges;

  friend std::istream& operator>>(std::istream& sin, Store& s) {
    s.ranges.clear();
    for (std::string range; std::getline(sin, range, ',') && !range.empty();) {
      s.ranges.emplace_back(range);
    }
    return sin;
  }

  bool Invalid(const lli x) const {
    const int digits = 1 + std::floor(std::log10(x));
    if (digits & 1) return false;

    const lli p = std::pow(10, digits >> 1);
    const lli l = x / p, r = x % p;
    return l == r;
  }
  lli FindInvalids() const {
    lli sum = 0;
    for (const auto& r : ranges) {
      for (lli i = r.start; i <= r.end; ++i) {
        if (!Invalid(i)) continue;
        sum += i;
      }
    }
    return sum;
  }
};
template <>
struct std::formatter<Store> {
  constexpr auto parse(std::format_parse_context& ctx) {
    auto it = ctx.begin();
    return it;
  }
  template <class FormatContext>
  auto format(const Store& s, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "ranges: {}", s.ranges);
  }
};

int main() {
  Store store;
  std::cin >> store;
  std::println("store: {}", store);

  const lli ans = store.FindInvalids();
  std::println("Ans: {}", ans);

  return 0;
}