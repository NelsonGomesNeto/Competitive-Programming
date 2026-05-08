#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<int> a;
  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;

    std::set<int> rem;
    for (int i = 1; i <= n; ++i) rem.insert(i);

    bool can = true;
    for (int i = 0; i < n; ++i) {
      if (a[i] == -1) continue;
      auto it = rem.find(a[i]);
      if (it == rem.end())
        can = false;
      else
        rem.erase(it);
      continue;
    }
    if (can) {
      std::cout << "Yes\n";
      for (int i = 0; i < n; ++i) {
        if (a[i] != -1) continue;
        a[i] = *rem.begin();
        rem.erase(rem.begin());
      }
      for (int i = 0; i < n; ++i) {
        if (i) std::cout << " ";
        std::cout << a[i];
      }
      std::cout << "\n";
    } else {
      std::cout << "No\n";
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
