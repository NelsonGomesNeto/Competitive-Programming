#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  lli k;
  std::vector<lli> travelers;

  bool Solve() {
    std::cin >> n >> k;
    travelers.resize(n);
    for (lli& s : travelers) std::cin >> s;

    const lli min_s = *std::min_element(travelers.begin(), travelers.end());
    const lli total_time = n == 1 ? min_s : 2 * (n - 2) * min_s + min_s;
    return total_time <= k;
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const bool ans = test_case.Solve();
    std::cout << "Case #" << t << ": " << (ans ? "YES" : "NO") << "\n";
  }
  return 0;
}