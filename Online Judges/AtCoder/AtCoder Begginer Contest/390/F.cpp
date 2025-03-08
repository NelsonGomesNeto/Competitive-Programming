#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<int> a;

  // O(n^3)
  lli Naive() {
    lli ans = 0;
    for (int l = 0; l < n; ++l) {
      for (int r = l; r < n; ++r) {
        std::set<int> curr;
        for (int i = l; i <= r; ++i) curr.insert(a[i]);

        int skips = 0;
        int prv = -1;
        for (const auto ai : curr) {
          if (prv + 1 != ai) ++skips;
          prv = ai;
        }
        ans += skips;
      }
    }
    return ans;
  }

  std::vector<std::vector<int>> pos;
  int BinarySearch(const std::vector<int>& arr, const int v,
                   const bool upperbound) {
    if (arr.empty()) return -1;

    int lo = 0, hi = (int)arr.size() - 1;
    while (lo < hi) {
      const int mid = (lo + hi + upperbound) >> 1;
      if (upperbound) {
        if (arr[mid] <= v)
          lo = mid;
        else
          hi = mid - 1;
      } else {
        if (arr[mid] >= v)
          hi = mid;
        else
          lo = mid + 1;
      }
    }

    if (upperbound) {
      return arr[lo] <= v ? arr[lo] : -1;
    } else {
      return arr[lo] >= v ? arr[lo] : -1;
    }
  }
  int GetLimitBelow(const int x, const int p) {
    const int limit = BinarySearch(pos[x], p - 1, /*upperbound=*/true);
    return limit == -1 ? 0 : limit + 1;
  }
  int GetLimitAbove(const int x, const int p) {
    const int limit = BinarySearch(pos[x], p + 1, /*upperbound=*/false);
    return limit == -1 ? n - 1 : limit - 1;
  }
  // Count the number of pairs when `x` at position `p` will be part of an
  // operation when l = x.
  // In other works:
  //   * (x - 1) is not inside A[L : R]
  //   * x is inside A[L : R]
  lli CountValidPairs(const int x, const int p) {
    const int lo = std::max(GetLimitBelow(x - 1, p), GetLimitBelow(x, p));
    const int hi = GetLimitAbove(x - 1, p);
    const int ldist = p - lo + 1, rdist = hi - p + 1;
    return (lli)ldist * rdist;
  }
  lli Solve() {
    lli ans = 0;
    for (int x = 1; x <= n; ++x) {
      if (pos[x].empty()) continue;
      for (const auto p : pos[x]) {
        const lli res = CountValidPairs(x, p);
        ans += res;
      }
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    pos.resize(n + 1, std::vector<int>{});
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
      pos[a[i]].push_back(i);
    }

    // const lli naive_ans = Naive();
    // const lli ans2 = Solve2();
    const lli ans = Solve();
    // if (ans != naive_ans) std::cout << "\twrong! " << naive_ans << "\n";
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
