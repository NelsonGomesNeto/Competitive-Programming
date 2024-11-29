#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, c;
  std::vector<int> t;
  bool Solve() {
    if (!(std::cin >> n >> c)) return false;

    t.resize(n);
    for (int& ti : t) std::cin >> ti;

    int ans = 0, prv = -1e6;
    for (int ti : t) {
      if (ti - prv >= c) {
        ++ans;
        prv = ti;
      }
    }
    std::cout << ans << "\n";
    return true;
  }
};
TestCase test_case;

int main() {
  do {
    test_case = TestCase{};
  } while (test_case.Solve());
  return 0;
}
