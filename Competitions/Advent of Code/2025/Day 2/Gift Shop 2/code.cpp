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
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
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

    for (int div = 2; div <= digits; ++div) {
      if (digits % div != 0) continue;
      const int digits_per_div = digits / div;
      const lli p = std::pow(10, digits_per_div);

      const bool is_invalid = [&]() {
        lli prv = -1, curr = x;
        while (curr > 0) {
          const lli suffix = curr % p;
          if (prv == -1)
            prv = suffix;
          else if (prv != suffix)
            return false;
          curr /= p;
        }
        return true;
      }();
      if (is_invalid) return true;
    }
    return false;
  }
  lli FindInvalids() const {
    lli sum = 0;
    for (const auto& r : ranges) {
      for (lli i = r.start; i <= r.end; ++i) {
        if (!Invalid(i)) continue;
        sum += i;
        std::println("\tinvalid: {}", i);
      }
    }
    return sum;
  }
};
template <>
struct std::formatter<Store> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Store& s, FormatContext& ctx) const {
    std::format_to(ctx.out(), "ranges: [\n");
    for (const auto& r : s.ranges) {
      std::format_to(ctx.out(), "\t{},\n", r);
    }
    return std::format_to(ctx.out(), "]");
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