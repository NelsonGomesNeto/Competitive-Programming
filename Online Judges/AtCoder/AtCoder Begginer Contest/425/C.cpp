#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, q;
  std::vector<int> a;
  std::vector<lli> acc;

  int curr_shift;
  void Update(const int shift) { curr_shift = (curr_shift + shift) % n; }
  lli Sum(const int lo, const int hi) { return acc[hi + 1] - acc[lo]; }
  int Fix(const int pos) { return pos % n; }
  lli Query(const int lo, const int hi) {
    const int l = Fix(lo + curr_shift), r = Fix(hi + curr_shift);
    DEBUG std::cout << "\t" << l << " " << r << "\n";
    if (l > r) {
      return Sum(l, n - 1) + Sum(0, r);
    } else {
      return Sum(l, r);
    }
  }

  bool Run() {
    if (!(std::cin >> n >> q)) return false;
    a.resize(n), acc.resize(n + 1);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
      acc[i + 1] = acc[i] + a[i];
    }
    curr_shift = 0;

    for (int qi = 0; qi < q; ++qi) {
      int op;
      std::cin >> op;
      if (op == 1) {
        int shift;
        std::cin >> shift;
        Update(shift);
      } else {
        int l, r;
        std::cin >> l >> r;
        --l, --r;
        const lli ans = Query(l, r);
        std::cout << ans << "\n";
      }
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
