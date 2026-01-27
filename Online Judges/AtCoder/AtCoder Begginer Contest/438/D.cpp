#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const lli kInf = 1e16;

struct TestCase {
  int n;
  std::vector<int> a, b, c;
  std::vector<lli> bacc, cacc, bc;

  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    b.resize(n);
    c.resize(n);
    for (auto& ai : a) std::cin >> ai;
    for (auto& bi : b) std::cin >> bi;
    for (auto& ci : c) std::cin >> ci;

    bacc.resize(n + 1);
    for (int i = 0; i < n; ++i) {
      bacc[i + 1] = bacc[i] + b[i];
    }
    cacc.resize(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
      cacc[i] = cacc[i + 1] + c[i];
    }

    bc.resize(n, -kInf);
    std::multiset<lli> bcs;
    for (int i = 0, end = n - 1; i < end; ++i) {
      bc[i] = bacc[i + 1] + cacc[i + 1];
      bcs.insert(bc[i]);
    }

    lli ans = 0, a_sum = 0;
    for (int i = 0, end = n - 2; i < end; ++i) {
      a_sum += a[i];
      bcs.erase(bcs.find(bc[i]));
      const lli bc_sum = *bcs.rbegin() - bacc[i + 1];
      DEBUG std::println("\t{} | {} {} | {}", i, a_sum, bc_sum, a_sum + bc_sum);
      ans = std::max(ans, a_sum + bc_sum);
    }
    std::println("{}", ans);

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
