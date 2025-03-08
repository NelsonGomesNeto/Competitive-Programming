#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int x;
  bool Run() {
    if (!(std::cin >> x)) return false;

    int ans = 0;
    for (int i = 1; i <= 9; ++i)
      for (int j = 1; j <= 9; ++j) {
        int ij = i*j;
        if (ij == x) continue;
        ans += ij;
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
