#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::vector<std::pair<int, int>> lr;
  std::vector<std::vector<int>> in, out;

  lli AllCombinations(const int size) { return size; }

  int GetHighLimit(const int lo, const int i) {
    for (const int j : out[i]) {
      if (j < lo) continue;
      return i;
    }
    return n;
  }

  bool Run() {
    if (!(std::cin >> m >> n)) return false;

    lr.resize(m);
    in.resize(n, {}), out.resize(n, {});
    for (auto& [l, r] : lr) {
      std::cin >> l >> r;
      --l, --r;
      in[l].push_back(r), out[r].push_back(l);
    }

    lli ans = 0;
    int hi = 0;
    for (int i = 0; i < n; ++i) {
      int lo = i;
      int limit = GetHighLimit(lo, hi);
      while (hi + 1 < n) {
        int nxt_limit = std::min(limit, GetHighLimit(lo, hi + 1));
        if (hi + 1 >= nxt_limit) break;
        limit = nxt_limit, ++hi;
      }
      if (hi >= limit) continue;

      lli add = AllCombinations(hi - lo + 1);
      DEBUG std::cout << "\t" << lo + 1 << " " << hi + 1 << " | " << add
                      << " | " << out[hi].empty() << "\n";

      ans += add;
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
