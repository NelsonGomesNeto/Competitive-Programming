#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  std::string s;
  bool Run() {
    if (!(std::cin >> s)) return false;

    double ans = 0;
    for (int i = 0; i < s.size(); ++i) {
      for (int j = i + 2; j < s.size(); ++j) {
        if (s[i] != 't' || s[j] != 't') continue;
        int ts = 0;
        for (int k = i; k <= j; ++k) {
          ts += s[k] == 't';
        }
        double f = (double)(ts - 2) / ((j - i + 1) - 2);
        ans = std::max(ans, f);
      }
    }
    std::cout << std::setprecision(15) << ans << "\n";

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
