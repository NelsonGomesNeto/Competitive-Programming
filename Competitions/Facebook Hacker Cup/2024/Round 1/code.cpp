#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {

  int Solve() {
    return 343;
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const auto ans = test_case.Solve();
    std::cout << "Case #" << t << ": " << ans << "\n";
  }
  return 0;
}