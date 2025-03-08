#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

std::pair<lli, lli> Simplify(const int a, const int b) {
  lli g = std::gcd(a, b);
  return std::make_pair(a / g, b / g);
}

struct TestCase {
  int n;
  std::vector<int> a;
  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    for (int& ai : a) std::cin >> ai;

    bool is = true;
    const auto r = Simplify(a[1], a[0]);
    for (int i = 1; i < n; ++i) {
      const auto ri = Simplify(a[i], a[i - 1]);
      if (r != ri) {
        is = false;
        break;
      }
    }

    std::cout << (is ? "Yes" : "No") << "\n";

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
