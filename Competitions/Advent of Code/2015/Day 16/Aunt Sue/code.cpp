#include <bits/stdc++.h>

const int kTargetAunt = 0;

struct Aunt {
  const int id;
  const std::map<std::string, int> properties;
  Aunt(std::istringstream&& sin)
      : id([&]() {
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
          int num;
          sin >> num;
          return num;
        }()),
        properties([&]() {
          std::map<std::string, int> ps;
          std::string p;
          int num;
          while (true) {
            sin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            if (!(sin >> p)) break;
            assert(p.back() == ':');
            p.pop_back();
            sin >> num;
            ps[p] = num;
          }
          return ps;
        }()) {}
  Aunt(const std::string& str) : Aunt(std::istringstream(str)) {}
};
template <>
struct std::formatter<Aunt> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Aunt& a, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "{}: {}", a.id,
        a.properties |
            std::views::transform([](const std::pair<std::string, int>& kv) {
              const auto& [k, v] = kv;
              return std::format("{}: {}", k, v);
            }) |
            std::views::join_with(std::string_view(", ")) |
            std::ranges::to<std::string>());
  }
};

struct Mcfsam {
  const std::vector<Aunt> aunts;
  Mcfsam(std::istringstream&& sin)
      : aunts([&]() {
          std::vector<Aunt> as;
          for (std::string line; std::getline(sin, line);) {
            as.emplace_back(line);
          }
          return as;
        }()) {}
  Mcfsam(const std::string& str) : Mcfsam(std::istringstream(str)) {}

  int FindTargetAunt(const int id) const {
    const auto& target = aunts[id];
    for (const auto [i, a] : aunts | std::views::enumerate) {
      if (i == id) continue;
      const bool is_target = std::ranges::all_of(
          a.properties, [&](const std::pair<std::string, int>& kv) {
            const auto& [k, v] = kv;
            auto it = target.properties.find(k);
            assert(it != target.properties.end());
            return it->second == v;
          });
      if (is_target) return i;
    }
    assert(false);
  }
};
template <>
struct std::formatter<Mcfsam> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Mcfsam& m, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}",
                          m.aunts | std::views::transform([](const Aunt& a) {
                            return std::format("\t{}", a);
                          }) | std::views::join_with('\n') |
                              std::ranges::to<std::string>());
  }
};

int main() {
  std::stringstream ss;
  ss << std::cin.rdbuf();
  const std::string input = ss.str();

  Mcfsam machine(input);
  std::println("machine:\n{}", machine);

  const int ans = machine.FindTargetAunt(kTargetAunt);
  std::println("ans: {}", ans);

  return 0;
}
