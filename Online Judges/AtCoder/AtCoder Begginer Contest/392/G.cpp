#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
B - A = C - B

(B - A) - 0 = (C - A) - (B - A)
B - A = C - B

2*B = C + A
A = 2*B - C
C = 2*B - A
*/

const int kMaxS = 1e6;

struct TestCase {
  int n;
  std::vector<int> s[2], cnt[2];
  bool Run() {
    if (!(std::cin >> n)) return false;
    s[0].resize(n), s[1].resize(n);
    cnt[0].resize(kMaxS, 0);
    cnt[1].resize(kMaxS, 0);
    for (int i = 0; i < n; ++i) {
      int si;
      std::cin >> si;
      bool odd = si & 1;
      s[odd].push_back(si);
      cnt[odd].push_back(si);
    }
    std::sort(s[0].begin(), s[0].end());
    std::sort(s[1].begin(), s[1].end());

    lli ans = 0;
    for (int odd = 0; odd < 2; ++odd) {
      for (int i = 0; i < s[odd].size(); ++i) {
        const int a = s[odd][i];
        for (int j = i + 1; j < s[odd].size(); ++j) {
          const int b = s[odd][j];
          if (2 * b >= s[odd].back()) continue;
          const int c = 2 * b - a;
          ans += cnt[odd][c];
        }
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
