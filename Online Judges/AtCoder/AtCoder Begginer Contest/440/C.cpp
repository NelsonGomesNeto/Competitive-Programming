#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, w;
  std::vector<int> c;

  lli GetCost() {
    
  }

  bool Run() {
    if (!(std::cin >> n >> w)) return false;
    c.resize(n);
    for (auto& ci : c) std::cin >> ci;

    lli ans = std::numeric_limits<lli>::max();
    for (int x = 0, last = 2*w; x <= last; ++x) {
      ans = std::min(ans, GetCost(x));
    }
    return ans;

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
