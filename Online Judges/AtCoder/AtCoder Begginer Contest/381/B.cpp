#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const std::string kYes = "Yes", kNo = "No";

struct TestCase {
  std::string s;
  std::vector<int> cnt;

  std::string Solve() {
    if (s.size() & 1) return kNo;

    cnt.resize(255, 0);
    for (const char c : s) ++cnt[c];
    for (int i = 1, end = s.size() / 2; i <= end; ++i) {
      const int a = 2 * i - 1 - 1, b = 2 * i - 1;
      if (s[a] != s[b]) return kNo;
    }

    for (const int c : cnt)
      if (c != 0 && c != 2) return kNo;

    return kYes;
  }

  bool Run() {
    if (!(std::cin >> s)) return false;

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
