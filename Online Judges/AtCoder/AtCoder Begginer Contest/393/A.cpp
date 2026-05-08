#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  std::string a, b;
  bool Run() {
    if (!(std::cin >> a >> b)) return false;
    bool af = a == "fine", bf = b == "fine";

    auto PrintRes = [](const int x) {
      std::cout << x << "\n";
    };
    if (af && bf) {
      PrintRes(4);
    } else if (af && !bf) {
      PrintRes(3);
    } else if (!af && bf) {
      PrintRes(2);
    } else {
      PrintRes(1);
    }

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
