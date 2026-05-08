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

  std::vector<std::vector<int>> memo2;
  bool IsSingleColor(const int lo, const int hi) {
    int& ans = memo2[lo][hi];
    if (ans != -1) return ans;
    if (c[lo] != c[hi]) return ans = false;
    std::vector<int>& positions = pos_by_color[c[lo]];
    const int range_size =
        std::distance(
            std::lower_bound(positions.begin(), positions.end(), lo),
            std::lower_bound(positions.begin(), positions.end(), hi)) +
        1;
    return ans = (hi - lo + 1) == range_size;
  }
  std::vector<std::vector<lli>> memo;
  lli Solve(const int lo, const int hi) {
    if (lo > hi) return 0;
    if (lo == hi) return 1 + x[c[lo]];
    if (IsSingleColor(lo, hi)) return (hi - lo + 1) + x[c[lo]];

    lli& ans = memo[lo][hi];
    if (ans != -1) return ans;

    ans = kInf;
    for (int i = lo; i <= hi; ++i) {
      // TODO: Handle circularity!
      for (int j = hi; j <= hi; ++j) {
        const lli res = Solve(lo, i - 1) + Solve(j + 1, hi);

        // pick one color from range and paint it as that color, then solve for
        // every other range
        std::unordered_map<int, lli> sum_by_color;
        lli total_sum = 0;
        for (int k = i; k <= j; ++k) {
          int curr = k;
          while (curr + 1 <= j && c[curr + 1] == c[k]) ++curr;
          lli curr_sum = Solve(k, curr);
          sum_by_color[c[k]] += curr_sum, total_sum += curr_sum;
          k = curr;
        }

        for (const auto [color, sum] : sum_by_color) {
          const lli cost = (j - i + 1) + x[color];
          ans = std::min(ans, res + cost + (total_sum - sum));
        }
      }
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    c.resize(n), x.resize(n);
    pos_by_color.resize(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> c[i];
      --c[i];
      pos_by_color[c[i]].push_back(i);
    }
    for (auto& xi : x) std::cin >> xi;

    memo.resize(n, std::vector<lli>(n, -1));
    memo2.resize(n, std::vector<int>(n, -1));
    lli ans = Solve(0, n - 1);
    for (int i = 1; i < n; ++i) {
      for (auto& line : memo) std::fill(line.begin(), line.end(), -1);
      for (auto& line : memo2) std::fill(line.begin(), line.end(), -1);
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
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

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
