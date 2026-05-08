#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int r, x;
  bool Run() {
    if (!(std::cin >> r >> x)) return false;
    bool rated = false;
    if (x == 1) {
      rated = (r >= 1600 && r <= 2999);
    } else {
      rated = (r >= 1200 && r <= 2399);
    }
    std::cout << (rated ? "Yes" : "No") << "\n";
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
