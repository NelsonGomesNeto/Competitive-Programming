#include <bits/stdc++.h>
#define lli long long int

const int kTeaspoons = 100;

const int kPropertiesCount = 5;
const std::array<std::string, kPropertiesCount> kProperties = {
    "capacity", "durability", "flavor", "texture", "calories",
};
using properties_array = std::array<int, kPropertiesCount>;
const properties_array kNilProperties = properties_array{0, 0, 0, 0, 0};
lli GetValue(const properties_array& properties) {
  lli ans = 1;
  // skip calories
  for (const int& pi : properties | std::views::take(4)) {
    ans *= std::max(pi, 0);
  }
  return ans;
}
void Add(properties_array& a, const properties_array& b) {
  for (auto [ai, bi] : std::views::zip(a, b)) {
    ai += bi;
  }
}
void Sub(properties_array& a, const properties_array& b) {
  for (auto [ai, bi] : std::views::zip(a, b)) {
    ai -= bi;
  }
}

struct Ingredient {
  const std::string name;
  const properties_array properties;
  Ingredient(std::istringstream&& sin)
      : name([&]() {
          std::string s;
          sin >> s;
          assert(s.back() == ':');
          s.pop_back();
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
          return s;
        }()),
        properties([&]() {
          properties_array ps;
          for (auto& pi : ps) {
            sin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            sin >> pi;
            sin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
          }
          return ps;
        }()) {}
  Ingredient(const std::string& str) : Ingredient(std::istringstream(str)) {}

  properties_array Teaspoons(const int k) const {
    properties_array ps = properties;
    for (auto& pi : ps) pi *= k;
    return ps;
  }
};
template <>
struct std::formatter<Ingredient> {
  bool has_max_name_size = false;
  std::size_t max_name_size_id;
  constexpr auto parse(std::format_parse_context& ctx) {
    auto it = ctx.begin();
    if (it == ctx.end() || *it == '}') return it;
    has_max_name_size = true;
    ++it;
    max_name_size_id = ctx.next_arg_id();
    ++it;
    return it;
  }
  template <class FormatContext>
  auto format(const Ingredient& i, FormatContext& ctx) const {
    if (has_max_name_size) {
      auto arg = ctx.arg(max_name_size_id);
      const int max_name_size = std::visit_format_arg(
          [](auto&& val) -> int {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_integral_v<T>) {
              return static_cast<int>(val);
            } else {
              assert(false);
            }
          },
          arg);
      return std::format_to(ctx.out(), "{:{}}: {}", i.name, max_name_size,
                            i.properties);
    } else {
      return std::format_to(ctx.out(), "{}: {}", i.name, i.properties);
    }
  }
};

struct Cookie {
  const std::vector<Ingredient> ingredients;
  Cookie(std::istringstream&& sin)
      : ingredients([&]() {
          std::vector<Ingredient> is;
          for (std::string line; std::getline(sin, line);) {
            is.emplace_back(line);
          }
          return is;
        }()) {}
  Cookie(const std::string& str) : Cookie(std::istringstream(str)) {}

  void FindBestCombinationRec(properties_array& curr, properties_array& best,
                              int i = 0, int rem = kTeaspoons) const {
    if (i == (int)ingredients.size()) {
      if (GetValue(curr) > GetValue(best)) best = curr;
      return;
    }
    for (int j = (i + 1 == (int)ingredients.size() ? rem : 0); j <= rem; ++j) {
      Add(curr, ingredients[i].Teaspoons(j));
      FindBestCombinationRec(curr, best, i + 1, rem - j);
      Sub(curr, ingredients[i].Teaspoons(j));
    }
    return;
  }
  lli FindBestCombination() const {
    std::println("FindBestCombination:");
    properties_array curr = kNilProperties, best = kNilProperties;
    FindBestCombinationRec(curr, best);
    const properties_array ans = best;
    std::println("\tans: {}", ans);
    return GetValue(ans);
  }
};
template <>
struct std::formatter<Cookie> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Cookie& c, FormatContext& ctx) const {
    const int max_name_size = std::ranges::max(
        c.ingredients | std::views::transform(
                            [](const Ingredient& i) { return i.name.size(); }));
    return std::format_to(
        ctx.out(), "{}",
        c.ingredients | std::views::transform([&](const Ingredient& i) {
          return std::format("\t{:{}}", i, max_name_size);
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>());
  }
};

int main() {
  std::stringstream ss;
  ss << std::cin.rdbuf();
  std::string input = ss.str();

  const Cookie cookie(input);
  std::println("cookie:\n{}", cookie);

  const int ans = cookie.FindBestCombination();
  std::println("ans: {}", ans);

  return 0;
}
