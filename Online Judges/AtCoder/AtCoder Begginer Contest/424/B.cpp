#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m, k;
  std::vector<std::set<int>> c;
  bool Run() {
    if (!(std::cin >> n >> m >> k)) return false;

    c.resize(n, std::set<int>{});
    std::vector<int> ans;
    for (int i = 0; i < k; ++i) {
      int person, problem;
      std::cin >> person >> problem;
      --person, --problem;
      c[person].insert(problem);
      if ((int)c[person].size() == m)
        ans.push_back(person);
    }

    for (int i = 0; i < (int)ans.size(); ++i) {
      if (i) std::cout << " ";
      std::cout << (ans[i] + 1);
    }
    std::cout << "\n";

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
