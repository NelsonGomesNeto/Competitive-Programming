#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct ResAndCnt {
  lli res;
  int cnt;
  bool operator<(const ResAndCnt& other) const {
    return res < other.res || (res == other.res && cnt < other.cnt);
  }
};
const ResAndCnt kNil = {-1, -1};

struct TestCase {
  int n, k, l;
  std::string handle;
  std::vector<bool> is_upper;

  bool target_is_upper_;
  std::vector<ResAndCnt> memo;
  lli penalty_;
  ResAndCnt EvalWithPenalty(const int i) {
    // if (i >= n) return {k * penalty_, 0};
    if (i >= n) return {n - i, 0};
    auto& ans = memo[i];
    if (ans.cnt != -1) return ans;

    auto no_pick = EvalWithPenalty(i + 1);
    no_pick.res += target_is_upper_ == is_upper[i];

    auto pick = EvalWithPenalty(i + l);
    pick.res += l - penalty_, ++pick.cnt;

    return ans = std::max(no_pick, pick);
  }
  ResAndCnt Eval(const lli penalty) {
    return EvalBottomUp(penalty);

    // penalty_ = penalty;
    // if (memo.empty())
    //   memo.resize(n, kNil);
    // else
    //   std::fill(memo.begin(), memo.end(), kNil);
    // return EvalWithPenalty(/*i=*/0);
  }
  ResAndCnt EvalBottomUp(const lli penalty) {
    if (memo.empty()) memo.resize(n + 1);
    memo[n] = {0, 0};

    for (int i = n - 1; i >= 0; --i) {
      auto& ans = memo[i];

      auto no_pick = memo[i + 1];
      no_pick.res += target_is_upper_ == is_upper[i];

      int minl = std::min(l, n - i);
      auto pick = memo[i + minl];
      pick.res += minl - penalty, ++pick.cnt;

      ans = std::max(no_pick, pick);
    }

    return memo[0];
  }

  int ConvertAndCount(const bool upper) {
    target_is_upper_ = upper;
    lli lo = 0, hi = 2e6;
    while (lo < hi) {
      const lli mid = (lo + hi + 1) >> 1;
      const auto [res, cnt] = Eval(mid);
      if (cnt >= k)
        lo = mid;
      else
        hi = mid - 1;
    }
    const auto [res, cnt] = Eval(lo);
    DEBUG std::cout << "\t\t" << lo << " " << res << " " << cnt << "\n";
    const int ans = res + lo * k;
    DEBUG std::cout << "\t" << upper << " | " << ans << " " << n - ans << "\n";
    return n - ans;
  }

  bool Run() {
    if (!(std::cin >> n >> k >> l)) return false;
    std::cin >> handle;
    is_upper.resize(n);
    for (int i = 0; i < n; ++i) {
      is_upper[i] = handle[i] >= 'A' && handle[i] <= 'Z';
    }

    const int ans = std::min(ConvertAndCount(/*upper=*/false),
                             ConvertAndCount(/*upper=*/true));
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
