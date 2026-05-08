#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kMaxN = 5e3;
const lli kMod = 998244353LL;

struct TestCase {
  int n;
  std::vector<int> balls_by_color;

  // std::array<std::array<lli, kMaxN + 1>, kMaxN> memo;
  std::array<std::map<int, lli>, kMaxN> memo;
  lli Solve(int i = 0, int sum = 0) {
    if (i == n) {
      // std::println("\t{}", sum);
      return (sum + 1) >> 1;
    }
    auto it = memo[i].find(sum);
    if (it != memo[i].end()) return it->second;
    lli& ans = it->second;
    ans =
        (Solve(i + 1, sum) + Solve(i + 1, sum + balls_by_color[i])) %
        kMod;
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    balls_by_color.resize(n);
    for (int& bi : balls_by_color) std::cin >> bi;

    for (int i = 0; i < n; ++i) {
      // std::ranges::fill(memo[i], -1);
      memo[i].clear();
    }
    const lli ans = Solve();
    std::println("{}", ans);

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
