#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, q;
  std::vector<int> a;
  std::vector<lli> acc;
  bool Run() {
    if (!(std::cin >> n >> q)) return false;
    a.resize(n), acc.resize(n + 1);
    for (auto& ai : a) std::cin >> ai;
    std::sort(a.begin(), a.end());
    acc[0] = 0;
    for (int i = 0; i < n; ++i) {
      acc[i + 1] = acc[i] + a[i];
    }

    for (int qi = 0; qi < q; ++qi) {
      lli b;
      std::cin >> b;

      if (b > a.back()) {
        std::cout << "-1\n";
        continue;
      }

      if (b == 1) {
        std::cout << "1\n";
        continue;
      }

      int pos = std::lower_bound(a.begin(), a.end(), b) - a.begin();
      lli ans = acc[pos] + (b - 1) * (n - pos) + 1;
      std::cout << ans << "\n";
    }

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
