#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::vector<int> a;
  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    a.resize(m);
    for (auto& ai : a) std::cin >> ai;
    std::sort(a.begin(), a.end());

    std::vector<int> ans;
    for (int i = 1; i <= n; ++i) {
      if (std::binary_search(a.begin(), a.end(), i)) continue;
      ans.push_back(i);
    }
    std::cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); ++i) {
      std::cout << ans[i] << (i + 1 == ans.size() ? "\n" : " ");
    }

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
