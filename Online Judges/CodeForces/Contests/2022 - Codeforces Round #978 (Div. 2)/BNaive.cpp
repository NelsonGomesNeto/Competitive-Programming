#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, x;
  std::vector<int> a;
  std::vector<int> cars;

  lli Hehe2(std::vector<int> curr, int i = 0, int j = 0, bool done = false) {
    if (i == curr.size()) return done ? Hehe(curr) : 1e6;
    if (j == x) return done ? Hehe(curr) : 1e6;

    lli ans = Hehe2(curr, i + 1, j, done);
    if (curr[i] != 0) {
      curr[i] -= 1;
      ans = std::min(ans, Hehe2(curr, i + 1, j + 1, true));
    }
    return ans;
  }
  lli Hehe(std::vector<int> curr) {
    if (*std::max_element(curr.begin(), curr.end()) == 0) {
      return 0;
    }
    return Hehe2(curr) + 1;
  }

  lli Solve() {
    std::cin >> n >> x;
    a.resize(n);
    for (int& ai : a) {
      std::cin >> ai;
      cars.push_back(ai);
    }

    lli ans = Hehe(cars);
    return ans;
  }
};
TestCase test_case;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const auto ans = test_case.Solve();
    std::cout << ans << "\n";
  }
  return 0;
}
