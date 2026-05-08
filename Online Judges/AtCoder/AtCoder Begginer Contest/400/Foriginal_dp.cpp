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
  std::vector<std::vector<int>> pos_by_color;

  std::vector<std::vector<lli>> memo;
  lli Solve(const int lo, const int hi) {
    if (lo > hi) return 0;
    if (lo == hi) return 1 + x[c[lo]];

    lli& ans = memo[lo][hi];
    if (ans != -1) return ans;

    ans = kInf;
    // We don't need to define both the starting and ending point of the cut
    // Fixing the start at `lo` and looking for a new `hi` is enough!
    for (int j = lo; j <= hi; ++j) {
      const lli rem = Solve(j + 1, hi);

      // We probably can do this inner O(n) part in O(lg(n)) by maintaining some
      // sets hihi.

      // pick one color from range and paint it as that color, then solve for
      // every other range
      std::unordered_map<int, lli> sum_by_color;
      lli total_sum = 0;
      for (int i = lo; i <= j; ++i) {
        int k = i;
        while (k + 1 <= j && c[(k + 1)] == c[i]) ++k;
        lli curr_sum = (k - i + 1) + x[c[i]];
        sum_by_color[c[i]] += curr_sum, total_sum += curr_sum;
        i = k;
      }

      for (const auto& [color, sum] : sum_by_color) {
        const lli cost = (j - lo + 1) + x[color];
        // We want to minimize cost - sum
        // `cost` is grows linearly for every color, so we can consider just the
        // color's original cost x[color].
        // `sum` varies on each iteration
        ans = std::min(ans, rem + cost + (total_sum - sum));
      }
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    c.resize(n), x.resize(n);
    pos_by_color.resize(n, {});
    for (int i = 0; i < n; ++i) {
      std::cin >> c[i];
      --c[i];
      pos_by_color[c[i]].push_back(i);
    }
    for (auto& xi : x) std::cin >> xi;

    memo.resize(n, std::vector<lli>(n, -1));
    lli ans = Solve(0, n - 1);
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
