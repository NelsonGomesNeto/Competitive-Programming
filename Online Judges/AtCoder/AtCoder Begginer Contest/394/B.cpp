#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<std::pair<int, std::string>> s;
  bool Run() {
    if (!(std::cin >> n)) return false;
    s.resize(n);
    for (auto& [l, si] : s) {
      std::cin >> si;
      l = si.size();
    }
    std::sort(s.begin(), s.end());
    std::string ans;
    for (const auto& [_, si] : s) ans.append(si);
    std::cout << ans << "\n";
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
