#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::vector<int> a, b;

  std::vector<std::vector<int>> memo;
  int GetValue(const int i, const bool flipped) {
    return flipped ? b[0] - a[i] : a[i];
  }
  int Solve(int i = 0, bool flipped = false) {
    if (i == a.size()) {
      return true;
    }
    int& ans = memo[i][flipped];
    if (ans != -1) return ans;

    ans = false;
    if (i) {
      if (GetValue(i - 1, flipped) <= GetValue(i, false))
        ans = Solve(i + 1, false);
      if (GetValue(i - 1, flipped) <= GetValue(i, true))
        ans = std::max(ans, Solve(i + 1, true));
    } else {
      ans = std::max(Solve(i + 1, false), Solve(i + 1, true));
    }

    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    a.resize(n), b.resize(m);
    for (auto& ai : a) std::cin >> ai;
    for (auto& bi : b) std::cin >> bi;

    a.resize(std::distance(a.begin(), std::unique(a.begin(), a.end())));

    memo.resize(a.size(), std::vector<int>(2, -1));
    int can = Solve();
    std::cout << (can ? "YES" : "NO") << "\n";

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
