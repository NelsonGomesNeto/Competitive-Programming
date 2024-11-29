#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<int> a;

  int Solve() {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (i + 1 < n && a[i] == a[i + 1]) {
        std::set<int> has;
        int res = 0, j = i;
        while (j + 1 < n && a[j] == a[j + 1] && !has.count(a[j])) {
          has.insert(a[j]);
          res += 2, j += 2;
        }
        ans = std::max(ans, res);
      }
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    for (int& ai : a) std::cin >> ai;

    int ans = Solve();

    std::cout << ans << "\n";

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
