#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const lli kMax = 1e9;

struct TestCase {
  lli n; int m;
  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    lli x = 0, curr = 1;
    bool possible = true;
    for (int i = 0; i <= m; ++i) {
      x += curr;
      curr *= n;
      if (x > kMax) {
        x = -1;
        break;
      }
    }
    if (x == -1) std::cout << "inf\n";
    else std::cout << x << "\n";
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
