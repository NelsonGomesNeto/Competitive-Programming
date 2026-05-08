#include <bits/stdc++.h>
#define lli long long int

const int kBatteriesCount = 12;

struct Bank {
  const std::vector<int> batteries;
  Bank(std::istream&& sin)
      : batteries([&]() {
          std::vector<int> b;
          char digit;
          while (sin >> digit) {
            b.push_back(digit - '0');
          }
          return b;
        }()) {}
  Bank(const std::string& raw_batteries)
      : Bank(std::istringstream(raw_batteries)) {}

  lli MaxJoltage() const {
    lli joltage = 0;
    auto lo = batteries.begin();
    for (int i = 0; i < kBatteriesCount; ++i) {
      const auto it = std::max_element(
          i ? std::next(lo) : batteries.begin(),
          batteries.begin() +
              ((int)batteries.size() - (kBatteriesCount - i) + 1));
      assert(it != batteries.end());

      joltage = joltage * 10 + (*it);
      lo = it;
    }
    return joltage;
  }
};
template <>
struct std::formatter<Bank> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Bank& b, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "batteries: {} - MaxJoltage: {}",
                          b.batteries, b.MaxJoltage());
  }
};

struct Power {
  std::vector<Bank> banks;

  friend std::istream& operator>>(std::istream& sin, Power& p) {
    p.banks.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      p.banks.emplace_back(line);
    }
    return sin;
  }

  lli TotalOutput() const {
    lli sum = 0;
    for (const auto& b : banks) {
      sum += b.MaxJoltage();
    }
    return sum;
  }
};
template <>
struct std::formatter<Power> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Power& p, FormatContext& ctx) const {
    std::format_to(ctx.out(), "banks: [\n");
    for (const auto& b : p.banks) {
      std::format_to(ctx.out(), "{}\n", b);
    }
    return std::format_to(ctx.out(), "]");
  }
};

int main() {
  Power power;
  std::cin >> power;
  std::println("power: {}", power);

  const lli ans = power.TotalOutput();
  std::println("Ans: {}", ans);

  return 0;
}
