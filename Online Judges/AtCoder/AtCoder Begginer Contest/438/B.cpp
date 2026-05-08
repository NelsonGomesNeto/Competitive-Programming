#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::string s, t;
  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    std::cin >> s >> t;

    int best = std::numeric_limits<int>::max();
    for (int i = 0; i + m - 1 < n; ++i) {
      int cost = 0;
      for (int j = 0; j < m; ++j) {
        int from = t[j] - '0', to = s[i + j] - '0';
        while (from != to) {
          ++cost, ++from;
          if (from == 10) from = 0;
        }
      }
      best = std::min(best, cost);
    }
    std::println("{}", best);

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
