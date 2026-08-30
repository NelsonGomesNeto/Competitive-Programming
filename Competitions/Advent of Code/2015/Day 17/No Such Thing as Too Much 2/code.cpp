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

  void AllCombinations(std::vector<int>& count_by_count, const int i,
                       const int rem, const int count) const {
    if (rem == 0) {
      ++count_by_count[count];
      return;
    }
    if (rem < 0 || i == (int)containers.size()) return;

    AllCombinations(count_by_count, i + 1, rem, count);
    AllCombinations(count_by_count, i + 1, rem - containers[i], count + 1);
  }
  int AllCombinations() const {
    std::println("AllCombinations:");
    std::vector<int> count_by_count(containers.size() + 1, 0);
    AllCombinations(count_by_count, /*i=*/0, target, /*count=*/0);
    std::println("{}", count_by_count | std::views::enumerate |
                           std::views::transform([](const auto& ic) {
                             const auto [i, c] = ic;
                             return std::format("\t{}: {}", i, c);
                           }) |
                           std::views::join_with('\n') |
                           std::ranges::to<std::string>());
    auto it = std::ranges::find_if(count_by_count,
                                   [](const int cnti) { return cnti > 0; });
    return *it;
  }
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

  const int ans = inventory.AllCombinations();
  std::println("ans: {}", ans);

  return 0;
}
