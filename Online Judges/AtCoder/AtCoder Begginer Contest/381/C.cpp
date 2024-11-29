#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::string s;

  int Expand(const int start) {
    int res = 1, i = start - 1, j = start + 1;
    while (i >= 0 && j < s.size() && s[i] == '1' && s[j] == '2') {
      res += 2, --i, ++j;
    }
    return res;
  }
  int Solve() {
    int ans = 1;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '/') {
        ans = std::max(ans, Expand(i));
      }
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    std::cin >> s;

    std::cout << Solve() << "\n";

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
