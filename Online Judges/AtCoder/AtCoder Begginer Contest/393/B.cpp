#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  std::string s;
  bool Run() {
    if (!(std::cin >> s)) return false;

    int ans = 0;
    for (int i = 0; i < s.size(); ++i) {
      for (int j = i + 1; j < s.size(); ++j) {
        int dist = j - i;
        int k = j + dist;
        if (k >= (int)s.size()) break;
        if (s[i] != 'A' || s[j] != 'B' || s[k] != 'C') continue;
        ++ans;
      }
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
