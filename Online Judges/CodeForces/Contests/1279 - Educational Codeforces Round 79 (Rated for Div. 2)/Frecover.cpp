#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
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

bool IsUpper(const char c) { return c >= 'A' && c <= 'Z'; }

struct TestCase {
  int n, k, l;
  std::string handle;
  std::vector<bool> is_upper;
  std::vector<int> is_upper_acc;

  int RangeSum(const bool upper, const int lo, const int hi) {
    const int upper_sum = is_upper_acc[hi + 1] - is_upper_acc[lo];
    return upper ? upper_sum : (hi - lo + 1) - upper_sum;
  }

  bool target_is_upper_;
  std::vector<ResAndCnt> memo;
  std::vector<bool> path;
  ResAndCnt Eval(const lli penalty) { return EvalBottomUp(penalty); }
  ResAndCnt EvalBottomUp(const lli penalty) {
    if (memo.empty()) memo.resize(n + 1), path.resize(n + 1);
    memo[n] = {0, 0};

    for (int i = n - 1; i >= 0; --i) {
      auto& ans = memo[i];

      auto no_pick = memo[i + 1];
      no_pick.res += target_is_upper_ == is_upper[i];

      int minl = std::min(l, n - i);
      auto pick = memo[i + minl];
      pick.res += minl - penalty, ++pick.cnt;

      path[i] = no_pick < pick;
      ans = std::max(no_pick, pick);
    }

    return memo[0];
  }
  // TODO(nelsongomesn): cnt - k picks which contribute the lowest towards the
  // answer and pray.
  int RecoverAnswer(const int cnt) {
    DEBUG2 std::cout << "\tRecovered answer "
                     << (target_is_upper_ ? "upper" : "lower")
                     << (cnt > k ? " | lagrange picks more!" : "") << "\n";
    std::vector<std::pair<int, int>> choices;
    for (int i = 0; i < n; ++i) {
      const bool picks = path[i];
      if (!picks) continue;
      const int minl = std::min(l, n - i);
      choices.emplace_back(RangeSum(!target_is_upper_, i, i + minl - 1), i);
      i += minl - 1;
    }
    std::sort(choices.begin(), choices.end(),
              std::greater<std::pair<int, int>>());
    choices.resize(std::min((int)choices.size(), k));
    DEBUG2 {
      std::cout << "\tchoices (" << cnt << "):";
      for (const auto& [contrib, i] : choices)
        std::cout << " (" << i << "," << contrib << ")";
      std::cout << "\n";
    }

    std::string s = handle;
    for (const auto [_, i] : choices) {
      const int minl = std::min(l, n - i);
      for (int j = 0; j < minl; ++j)
        s[i + j] =
            target_is_upper_ ? std::toupper(s[i + j]) : std::tolower(s[i + j]);
    }
    DEBUG2 std::cout << "\tbefore: " << handle << "\n";
    DEBUG2 std::cout << "\tafter : " << s << "\n";

    int ans = 0;
    for (const char c : s) ans += target_is_upper_ == IsUpper(c);
    DEBUG2 std::cout << "\trecovered_ans: " << (n - ans) << "\n";

    return ans;
  }

  int ConvertAndCount(const bool upper) {
    target_is_upper_ = upper;
    lli lo = 0, hi = 2e6;
    while (lo < hi) {
      const lli mid = (lo + hi + 1) >> 1;
      const auto [_, cnt] = Eval(mid);
      if (cnt >= k)
        lo = mid;
      else
        hi = mid - 1;
    }
    const auto [res, cnt] = Eval(lo);
    const int recovered_ans = RecoverAnswer(cnt);
    const int ans = res + lo * k;
    DEBUG2 std::cout << "\tactual_ans   : " << n - ans << "\n";
    assert(ans == recovered_ans);
    return n - recovered_ans;
  }

  bool Run() {
    if (!(std::cin >> n >> k >> l)) return false;
    std::cin >> handle;
    is_upper.resize(n), is_upper_acc.resize(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      is_upper[i] = IsUpper(handle[i]);
      is_upper_acc[i + 1] = is_upper_acc[i] + is_upper[i];
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
