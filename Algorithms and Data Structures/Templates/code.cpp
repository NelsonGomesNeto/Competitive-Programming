#include <bits/stdc++.h>
#ifdef DEB
#define DEBUG if (1)
#else
#define DEBUG if (0)
#endif
#define lli long long int
#define ldouble long double

struct TestCase {
  bool Run() {
    if (!(std::cin)) return false;
    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  DEBUG std::cout << "debug";
  else std::cout << "not debug";

  return 0;

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
