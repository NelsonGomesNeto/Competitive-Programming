#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
operation_cost = |range| + color_cost
for each color:
  dp on finding the minimum cost for a range
Doing this for each color doesn't work because the order matters, example:
  Suppose the best action for color x is [1 : 3] and for color y is also [1 : 3]
  Then, we can't use the best action for one of them

However, if we revert the problem and try to find the minimum cost of making all
items color = 0, then we can do a very similar range dp \o/.
*/

const lli kInf = 1e18;

struct TestCase {
  int n;
  std::vector<int> c, x;

  std::vector<std::vector<lli>> memo;
  lli Solve(const int lo, const int hi) {
    if (lo > hi) return 0;
    if (lo == hi) return 1 + x[c[lo]];

    lli& ans = memo[lo][hi];
    if (ans != -1) return ans;

    ans = kInf;
    lli total_sum = 0;
    std::unordered_map<int, lli> sum_by_color;
    std::set<std::pair<lli, int>> best_by_color;
    int previous_color = -1, current_length = 1;
    for (int j = lo; j <= hi; ++j) {
      const lli rem = Solve(j + 1, hi);
      const int current_color = c[j];

      if (current_color == previous_color)
        ++current_length;
      else
        current_length = 1;

      auto [sum_it, inserted] = sum_by_color.emplace(current_color, 0LL);

      auto best_it = best_by_color.find(
          {x[current_color] - sum_it->second, current_color});
      if (best_it != best_by_color.end()) best_by_color.erase(best_it);

      const lli to_add = 1 + (current_length == 1 ? x[current_color] : 0);
      sum_it->second += to_add, total_sum += to_add;
      best_by_color.emplace(x[current_color] - sum_it->second, current_color);

      // for (int i = lo; i <= j; ++i) {
      //   int k = i;
      //   while (k + 1 <= j && c[(k + 1)] == c[i]) ++k;
      //   lli curr_sum = (k - i + 1) + x[c[i]];
      //   sum_by_color[c[i]] += curr_sum, total_sum += curr_sum;
      //   i = k;
      // }

      // for (const auto& [color, sum] : sum_by_color) {
      //   const lli cost = (j - lo + 1) + x[color];
      //   // We want to minimize cost - sum
      //   // `cost` is grows linearly for every color, so we can consider just
      //   the
      //   // color's original cost x[color].
      //   // `sum` varies on each iteration
      //   ans = std::min(ans, rem + cost + (total_sum - sum));
      // }

      const auto& [cost_minus_sum, color] = *best_by_color.begin();
      const lli extra_cost = (j - lo + 1);
      ans = std::min(ans, rem + total_sum + extra_cost + cost_minus_sum);

      previous_color = c[j];
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    c.resize(n), x.resize(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> c[i];
      --c[i];
    }
    for (auto& xi : x) std::cin >> xi;

    memo.resize(n, std::vector<lli>(n, -1));
    lli ans = Solve(0, n - 1);
    // Try all rotations of `c` \o/.
    for (int i = 1; i < n; ++i) {
      for (auto& line : memo) std::fill(line.begin(), line.end(), -1);
      std::rotate(c.begin(), c.begin() + 1, c.end());
      lli res = Solve(0, n - 1);
      ans = std::min(ans, res);
    }
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
