#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m, k;

  bool Run() {
    if (!(std::cin >> n >> m >> k)) return false;

    if (k > std::max(n, m)) {
      std::cout << "-1\n";
      return true;
    }

    std::string ans;
    const int consecutive = k;
    auto Try = [&](const bool start) {
      ans.clear();
      if (start) {
        if (m == 0) return false;
        ans.push_back('1');
      } else {
        if (n == 0) return false;
        ans.push_back('0');
      }

      bool can = true;
      while (n && m) {
        if (ans.back() == '1')
          ans.push_back('0'), --n;
        else if (ans.back() == '0')
          ans.push_back('1'), --m;
      }
      auto CountConsecutive = [&ans](const char x) {
        int cnt = 0;
        for (int i = (int)ans.size() - 1; i >= 0; --i) {
          if (ans[i] != x) return cnt;
          ++cnt;
        }
        return cnt;
      };
      ans.append(std::string(std::max(n, m), n ? '0' : '1'));
      if (CountConsecutive('0') != k && CountConsecutive('1') != k) {
        return false;
      } else {
      }
      return can;
    };

    if (!Try(false) && !Try(true))
      std::cout << "-1\n";
    else
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
