#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  std::string s;
  bool Run() {
    if (!(std::cin >> s)) return false;

    std::vector<bool> has(256, 0);
    for (char c : s) has[c] = true;

    bool ans = has['A'] && has['B'] && has['C'];
    std::cout << (ans ? "Yes" : "No") << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
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
