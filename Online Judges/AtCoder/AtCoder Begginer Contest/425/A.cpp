#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  bool Run() {
    if (!(std::cin >> n)) return false;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
      ans += (i & 1 ? -1 : 1) * std::pow(i, 3);
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
