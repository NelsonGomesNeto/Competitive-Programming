#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int a, b, c, n;
  bool Run() {
    if (!(std::cin >> a >> b >> c >> n)) return false;

    const int maxv = std::max({a, b, c});
    int req = 3*maxv - (a + b + c);

    // req + x*3 = n
    // x = (n - req) / 3
    if (req > n || (n - req) % 3 != 0) {
      std::println("NO");
    } else {
      std::println("YES");
    }

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
