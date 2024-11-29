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
    for (int& ai : a) std::cin >> ai;

    int ans = 0;
    for (int j = 0; j < n; ++j) {
      auto Solve = [&](int i) -> int {
        std::set<int> done;
        std::list<int> curr;
        int res = 0;
        while (i + 1 < n && a[i] == a[i + 1]) {
          if (!done.count(a[i])) {
            done.insert(a[i]);
            curr.push_back(a[i]);
          } else {
            while (curr.front() != a[i]) {
              res -= 2;
              done.erase(curr.front());
              curr.pop_front();
            }
            curr.pop_front();
            curr.push_back(a[i]);
            res -= 2;
          }
          i += 2, res += 2;
          ans = std::max(ans, res);
        }
        if (res) return i - 2;
        return i;
      };
      j = std::max(Solve(j), Solve(j + 1));
      // --i;
    }

    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
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
