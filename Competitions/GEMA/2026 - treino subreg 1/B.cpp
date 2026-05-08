#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  std::string recipe;
  std::array<int, 3> ingredients;
  std::array<int, 3> costs;
  lli money;

  bool Run() {
    if (!(std::cin >> recipe)) return false;
    for (int& ii : ingredients) std::cin >> ii;
    for (int& ci : costs) std::cin >> ci;
    std::cin >> money;

    std::array<int, 256> ingredient_to_index;
    ingredient_to_index['B'] = 0, ingredient_to_index['S'] = 1,
    ingredient_to_index['C'] = 2;
    std::array<int, 3> recipe_ingredients;
    std::ranges::fill(recipe_ingredients, 0);
    for (const auto ri : recipe) {
      ++recipe_ingredients[ingredient_to_index[ri]];
    }

    const int base = std::min(
        {recipe_ingredients[0] == 0 ? std::numeric_limits<int>::max()
                                    : ingredients[0] / recipe_ingredients[0],
         recipe_ingredients[1] == 0 ? std::numeric_limits<int>::max()
                                    : ingredients[1] / recipe_ingredients[1],
         recipe_ingredients[2] == 0 ? std::numeric_limits<int>::max()
                                    : ingredients[2] / recipe_ingredients[2]});
    DEBUG std::println("\tbase: {}", base);
    for (auto [ii, ri] : std::views::zip(ingredients, recipe_ingredients)) {
      ii -= ri * base;
    }
    auto Can = [&](const lli x) {
      lli cost = 0;
      for (const auto [ii, ri, ci] :
           std::views::zip(ingredients, recipe_ingredients, costs)) {
        cost += ci * std::max(0LL, x * ri - ii);
      }
      DEBUG std::println("\t{} cost: {}", x, cost);
      return cost <= money;
    };
    lli lo = 0, hi = money;
    while (lo < hi) {
      const lli mid = (lo + hi + 1) >> 1;
      if (Can(mid))
        lo = mid;
      else
        hi = mid - 1;
    }
    const lli ans = base + lo;
    std::println("{}", ans);

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
