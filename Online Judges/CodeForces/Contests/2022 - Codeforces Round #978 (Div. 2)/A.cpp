#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, r;
  std::vector<int> a;
  int Solve() {
    std::cin >> n >> r;
    a.resize(n);
    for (int& aa : a) std::cin >> aa;

    int ans = 0, rem = 2*r;
    int to_seat = 0;
    for (const int ai : a) {
      if (ai & 1) {
        to_seat += 1;
        ans += ai - 1;
        rem -= ai - 1;
      } else {
        ans += ai;
        rem -= ai;
      }
    }

    DEBUG std::cout << ans << " | " << to_seat << " | " << rem << "\n";
    // 2*k + (to_seat - k) <= rem and k <= to_seat
    if (to_seat) {
      auto safe = [&](const int k) {
        return k <= to_seat && 2*k + to_seat - k <= rem;
      };
      int k = 0;
      while (safe(k + 1)) ++k;
      DEBUG std::cout << k << " | " << to_seat << " | " << rem << "\n";
      ans += k;
    }

    return ans;
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const auto ans = test_case.Solve();
    std::cout << ans << "\n";
  }
  return 0;
}
