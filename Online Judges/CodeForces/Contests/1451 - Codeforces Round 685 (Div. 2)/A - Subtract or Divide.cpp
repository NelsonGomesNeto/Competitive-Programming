#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  bool Run() {
    if (!(std::cin >> n)) return false;

    const int ans = [&]() {
      if (n == 1) return 0;
      if (n == 2) return 1;
      if (n == 3) return 2;
      if (~n & 1) return 2;
      return 3;
    }();
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
