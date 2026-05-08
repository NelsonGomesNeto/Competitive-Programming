#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, x;
  std::vector<int> a;

  lli Solve() {
    std::cin >> n >> x;
    a.resize(n);
    for (int& ai : a) {
      std::cin >> ai;
    }

    lli total_sum = 0, max_value = *std::max_element(a.begin(), a.end());
    for (const int ai : a) total_sum += ai;

    lli ans = std::max((lli)std::ceil((double)total_sum / x), max_value);

    return ans;
  }
};
TestCase test_case;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const auto ans = test_case.Solve();
    std::cout << ans << "\n";
  }
  return 0;
}
