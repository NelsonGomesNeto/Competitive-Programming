#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const lli kNil = std::numeric_limits<lli>::min();

struct TestCase {
  int n, capacity;
  std::vector<std::pair<int, lli>> items;

  std::vector<std::vector<lli>> memo;

  lli Eval(const int i, const int weight, const int k) {
    return Knapsack(i + 1, weight - k * items[i].first) + k * items[i].second -
           (lli)k * k;
  }

  lli Knapsack(const int i, const int weight) {
    if (i == n) return 0;

    lli& ans = memo[i][weight];
    if (ans != kNil) return ans;

    // Pick 0
    ans = Knapsack(i + 1, weight);

    // Pick 1 or more
    lli lo = 1, hi = weight / items[i].first;
    while (std::abs(hi - lo) > 3) {
      const lli midlo = (2 * lo + hi) / 3, midhi = (lo + 2 * hi) / 3;
      const lli elo = Eval(i, weight, midlo), ehi = Eval(i, weight, midhi);
      if (elo >= ehi) hi = midhi;
      if (ehi >= elo) lo = midlo;
    }

    for (lli k = lo; k <= hi; ++k) {
      ans = std::max(ans, Eval(i, weight, k));
    }

    return ans;
  }

  bool Solve() {
    if (!(std::cin >> n >> capacity)) return false;

    items.resize(n);
    for (auto& [w, v] : items) std::cin >> w >> v;

    memo.resize(n, std::vector<lli>(capacity + 1, kNil));
    const lli ans = Knapsack(0, capacity);
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  do {
    test_case = TestCase{};
  } while (test_case.Solve());

  return 0;
}