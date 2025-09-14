#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, k;
  std::vector<int> a, tmp;

  int Test(const int pos) {
    tmp = a;
    for (int i = pos, add = k; add >= 1 && i >= 0; --i, --add) {
      const int newai = a[i] + add;
      a[i] = newai;
    }
    const int res = *std::min_element(a.begin(), a.end());
    a = tmp;
    return res;
  }

  bool Run() {
    if (!(std::cin >> n >> k)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans = std::max(ans, Test(i));
    }
    std::cout << ans << "\n";

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
