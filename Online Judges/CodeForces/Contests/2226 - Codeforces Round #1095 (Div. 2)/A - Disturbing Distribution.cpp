#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<int> a;
  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    for (int& ai : a) std::cin >> ai;

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (a[i] == 1) {
        int j = i;
        while (j + 1 < n && a[j + 1] == 1) ++j;
        i = j;
        if (i + 1 == n) ans += 1;
      } else {
        ans += a[i];
      }
    }
    std::println("{}", ans);

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run();
  }

  return 0;
}
