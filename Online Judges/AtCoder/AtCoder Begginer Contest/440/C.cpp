#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
Thinking:
[1 : n]
paint i = C[i]

x -> paints all `i` such that (i + x) % 2W < W

We need to pick `x` once and only once such that it minimizes the cost. There
are no other restrictions in the problem description.

---
Solution:

It's fast to evaluate all values for x in [0 : 2*w - 1]. There are 2 levers at
play:
* y = n / 2*w (how many groups are there)
* z = 2*w (how many offsets to evaluate)
So, the complexity is O(y * z * group_eval) = O(n * group_eval). But, evaluating
a group can be done in O(1) through accumulated sums.
Finally, everything can be done in O(n) \o/.
*/

struct TestCase {
  int n, w;
  std::vector<int> c;
  std::vector<lli> acc;

  lli Evaluate(const int x) {
    std::vector<std::pair<int, int>> ranges;
    lli cost = 0;
    for (int k = 0;; ++k) {
      // minus `x` because we want to start at the i = -x mod 2*w so i + x = 0
      // mod 2*w.
      // [(2*w*k - x) : (2*w*k + w - 1 - x)]
      if (((2 * w * k + w - 1) - x) <= 0) continue;
      if (((2 * w * k) - x) > n) break;
      ranges.emplace_back(std::max(1, (2 * w * k) - x),
                          std::min(n, (2 * w * k + w - 1) - x));
      cost += acc[ranges.back().second + 1] - acc[ranges.back().first];
      if (((2 * w * k + w - 1) - x) > n) break;
    }
    DEBUG {
      std::vector<int> pos;
      for (int i = 1; i <= n; ++i) {
        if ((i + x) % (2 * w) < w) pos.push_back(i);
      }
      std::println("\tf({}) = {} | {} | {}", x, cost, ranges, pos);
    }
    return cost;
  }

  bool Run() {
    if (!(std::cin >> n >> w)) return false;
    c.resize(n + 1);
    acc.resize(n + 23);
    acc[0] = acc[1] = 0;
    for (auto [i, ci] : c | std::views::enumerate | std::views::drop(1)) {
      std::cin >> ci;
      acc[i + 1] = acc[i] + ci;
    }

    lli ans = std::numeric_limits<lli>::max();
    for (int x = 0, last = 2 * w - 1; x <= last; ++x) {
      const lli cost = Evaluate(x);
      ans = std::min(ans, cost);
    }
    std::println("{}", ans);

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run();
  }

  return 0;
}
