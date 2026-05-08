#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

const lli kInf = 1e15;
const std::pair<lli, int> kNil = {-1, -1};

struct TestCase {
  int n, k;
  std::vector<int> a;

  lli Naive(int i = 0, int cnt = 0, bool picking = false) {
    if (cnt > k) return -kInf;
    if (i == n) return cnt <= k ? 0 : -kInf;

    lli ans = std::max(
        Naive(i + 1, cnt, /*picking=*/false),
        Naive(i + 1, cnt + (picking == false), /*picking=*/true) + a[i]);

    return ans;
  }

  std::vector<std::vector<std::pair<lli, int>>> memo;
  std::pair<lli, int> Eval(const lli penalty, int i, bool picking) {
    if (i == n) return {0, 0};
    auto& ans = memo[i][picking];
    if (ans.first != -1) return ans;

    auto no_pick = Eval(penalty, i + 1, /*picking=*/false);
    auto pick = Eval(penalty, i + 1, /*picking=*/true);
    pick.first += a[i];
    if (!picking) pick.first -= penalty, ++pick.second;

    return ans = std::max(no_pick, pick);
  }

  std::pair<lli, int> Eval(const lli penalty) {
    if (memo.empty())
      memo.resize(n, std::vector<std::pair<lli, int>>(2, kNil));
    else
      for (int i = 0; i < n; ++i) memo[i][0] = memo[i][1] = kNil;
    return Eval(penalty, /*i=*/0, /*picking=*/false);
  }

  lli Solve() {
    lli lo = 0, hi = kInf;
    while (lo < hi) {
      lli mid = (lo + hi + 1) >> 1;
      const auto [_, cnt] = Eval(mid);
      if (cnt >= k)
        lo = mid;
      else
        hi = mid - 1;
    }
    const auto [res, cnt] = Eval(lo);
    DEBUG2 std::cout << "\t" << res << " " << cnt << " | " << lo << "\n";
    return res + lo * cnt;
  }

  bool Run() {
    if (!(std::cin >> n >> k)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;

    DEBUG {
      const lli naive_ans = Naive();
      std::cout << "naive: " << naive_ans << "\n";
    }

    const lli ans = Solve();
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
