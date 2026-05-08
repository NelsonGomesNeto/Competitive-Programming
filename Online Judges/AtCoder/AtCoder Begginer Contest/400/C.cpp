#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
X = 2^a * b^2
We can compute the number by finding the boundaries of `a` and `b`.
But that would overcount pairs where 2^a = b^2
  2^a = b^2
  2^a = (2^k)^2, b = 2^k
  2^a = 2^k*2
*/

struct TestCase {
  lli n;
  bool Run() {
    if (!(std::cin >> n)) return false;

    // for (lli n = 1; n <= 1e6; ++n) {
    lli cnt = 0;
    for (int a = 1; (1LL << a) <= n; ++a) {
      lli limit = n / (1LL << a);
      lli sqrt_limit = std::floor(std::sqrt((ldouble)limit));
      cnt += (sqrt_limit + 1) >> 1LL;
    }
    std::cout << cnt << "\n";
    // std::cout << n << ": " << cnt << "\n";
    // }

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // for (lli n = 1; n <= 1e6; ++n) {
  //   std::unordered_set<int> valid;
  //   for (int a = 1; (1LL << a) <= n; ++a) {
  //     for (int b = 1; ; ++b) {
  //       lli num = (1LL << a) * b * b;
  //       if (num > n) break;
  //       valid.insert(num);
  //     }
  //   }
  //   std::cout << n << ": " << (int)valid.size() << "\n";
  // }
  // return 0;

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
