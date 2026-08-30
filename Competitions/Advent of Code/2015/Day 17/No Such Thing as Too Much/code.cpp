#include <bits/stdc++.h>
#define lli long long int

struct Inventory {
  const int target;
  const std::vector<int> containers;
  Inventory(std::istringstream&& sin)
      : target([&]() {
          int t;
          sin >> t;
          return t;
        }()),
        containers([&]() {
          std::vector<int> cs;
          for (int c; sin >> c;) cs.push_back(c);
          std::ranges::sort(cs);
          return cs;
        }()) {}
  Inventory(const std::string& str) : Inventory(std::istringstream(str)) {}

  lli AllCombinations(const int i, const int rem) const {
    if (rem == 0) return 1;
    if (rem < 0 || i == (int)containers.size()) return 0;

    const lli ans = AllCombinations(i + 1, rem) +
                    AllCombinations(i + 1, rem - containers[i]);
    return ans;
  }
  lli AllCombinations() const { return AllCombinations(/*i=*/0, target); }
};
template <>
struct std::formatter<Inventory> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Inventory& i, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "\ttarget: {}\n\tcontainers: {}", i.target,
                          i.containers);
  }
};

int main() {
  std::stringstream ss;
  ss << std::cin.rdbuf();
  const std::string input = ss.str();

  const Inventory inventory(input);
  std::println("inventory:\n{}", inventory);

  const lli ans = inventory.AllCombinations();
  std::println("ans: {}", ans);

  return 0;
}
