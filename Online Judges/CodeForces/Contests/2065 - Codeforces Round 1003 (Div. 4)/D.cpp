#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::vector<std::pair<lli, std::vector<int>>> a;
  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    a.resize(n, std::make_pair(0, std::vector<int>(m)));
    for (auto& aa : a) {
      lli sum = 0, acc = 0;
      for (auto& ai : aa.second) {
        std::cin >> ai;
        acc += ai;
        sum += acc;
      }
      aa.first = acc;
    }
    std::sort(a.begin(), a.end());
    std::reverse(a.begin(), a.end());

    lli ans = 0, acc = 0;
    for (auto& aa : a) {
      for (auto& ai : aa.second) {
        acc += ai;
        ans += acc;
      }
    }
    std::cout << ans << "\n";

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
