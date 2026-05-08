#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<int> p, q, b;
  bool Run() {
    if (!(std::cin >> n)) return false;
    p.clear(), q.clear(), b.clear();
    p.resize(n), q.resize(n), b.resize(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> p[i];
      --p[i];
    }
    for (int i = 0; i < n; ++i) {
      std::cin >> q[i];
      --q[i];
      b[q[i]] = i;
    }

    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
      ans[i] = q[p[b[i]]] + 1;
    }
    for (int i = 0; i < n; ++i) {
      std::cout << ans[i] << (i + 1 == n ? "\n" : " ");
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
