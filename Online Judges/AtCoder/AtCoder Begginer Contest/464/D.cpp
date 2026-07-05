#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

std::vector<char> flip;

struct TestCase {
  int n;
  std::string s;
  std::vector<int> x, y;

  std::vector<std::vector<lli>> memo;
  lli Solve(int i, char prv) {
    if (i == n) {
      return 0;
    }
    lli& ans = memo[i][prv == 'R'];
    if (ans != -1) return ans;

    ans = 0;
    auto Try = [&](const lli cost, const char curr) {
      const lli gain = (prv == 'R' && curr == 'S') ? y[i] : 0;
      return Solve(i + 1, curr) - cost + gain;
    };
    ans = std::max(Try(0, s[i]), Try(x[i], flip[s[i]]));

    return ans;
  }
  lli Solve() { return Solve(/*i=*/0, /*prv=*/'S'); }

  bool Run() {
    if (!(std::cin >> n >> s)) return false;
    x.resize(n);
    for (auto& xin : x) std::cin >> xin;
    y.resize(n);
    for (auto& yin : y | std::views::drop(1)) std::cin >> yin;

    memo.resize(n, std::vector<lli>(2, -1));
    const lli ans = Solve();
    std::println("{}", ans);

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  flip.resize(256);
  flip['S'] = 'R';
  flip['R'] = 'S';

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run();
  }

  return 0;
}
