#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int

/*
Let's try to rephrase the problem a bit:
For each value `b`, find all the combinations with (x - b <= sum < x).
This way, all permutations of the chosen values are valid.
AND, `sum + b >= x`, so we just need to sum all of those occurrences.

We can use MeetInTheMiddle trick to split the sets into 2 and try to combine
them.
The merge is a bit tricky, but we can simply iterate over one of the sets, fix a
missing `b` and do a binary search to find the range in the other set.
With the range, we can find the sum of that range using a PrefixSum \o/.

This leads to O(2^(n/2)*n*log(2^(n/2))) which unfortunately I couldn't get to
pass a single test case.

After MANY interesting optimizations, I finally found that we can drop the `log`
by doing TwoPointers (sliding window). We just need to maintain multiple a
pointer for each `lo` bound to make sure everything stays sorted.

Overall, very interesting problem \o/.

It's worth mentioning that this solution allows to find all the cases while
the editorial solution is purely numerical and doesn't allow to easily find all
the cases where the bank sum is >= x.
*/

const lli kMod = 998244353LL;
lli ModPow(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1LL) ans = ans * x % kMod;
    x = x * x % kMod, y >>= 1LL;
  }
  return ans;
}
lli ModInv(lli x) { return ModPow(x, kMod - 2); }

struct TestCase {
  int n, n2;
  lli x;
  std::vector<lli> banks;
  std::vector<lli> pmemo;
  std::vector<lli> fat;

  lli Naive(int cnt = 0, lli curr = 0, lli mask = 0) {
    if (curr >= x) {
      return curr % kMod;
    }
    const lli p = ModInv(n - cnt);
    lli ans = 0;
    for (int i = 0; i < n; ++i) {
      if (mask & (1LL << i)) continue;
      ans = (ans +
             p * Naive(cnt + 1, curr + banks[i], mask | (1LL << i)) % kMod) %
            kMod;
    }
    return ans;
  }

  void BuildCasesRec(const std::vector<lli>& arr, int i = 0, int cnt = 0,
                     lli sum = 0) {
    // awesome optimization!!!
    if (sum >= x) return;
    if (i == (int)arr.size()) {
      if (sum >= pre_lo) b_cases[cnt].push_back(sum);
      return;
    }
    BuildCasesRec(arr, i + 1, cnt, sum);
    BuildCasesRec(arr, i + 1, cnt + 1, sum + arr[i]);
  }
  void BuildCases(const std::vector<lli>& arr) {
    b_cases.resize(arr.size() + 1);
    for (auto& ci : b_cases) ci.clear();
    BuildCasesRec(arr);
    for (auto& ci : b_cases) std::ranges::sort(ci, std::less());
  }
  std::vector<lli> a, b;
  std::vector<std::vector<lli>> b_cases, b_cases_acc;

  void BuildSumByMasks(const std::vector<lli>& arr, int i = 0, int mask = 0,
                       lli sum = 0) {
    if (i == (int)arr.size()) {
      sum_by_mask[mask] = {sum, mask};
      return;
    }
    BuildSumByMasks(arr, i + 1, mask, sum);
    BuildSumByMasks(arr, i + 1, mask | (1 << i), sum + arr[i]);
  }

  std::vector<std::pair<lli, int>> sum_by_mask;
  lli pre_lo;
  lli MeetInTheMiddle() {
    sum_by_mask.resize(1 << a.size());
    BuildSumByMasks(a);
    // Drop the case where all values are chosen.
    sum_by_mask.pop_back();
    std::ranges::sort(sum_by_mask, std::greater());
    while (!sum_by_mask.empty() && sum_by_mask.back().first >= x)
      sum_by_mask.pop_back();
    const int all_mask = ((1 << a.size()) - 1);
    pre_lo = x - std::reduce(a.begin(), a.end(), 0LL, std::plus());
    BuildCases(b);
    b_cases_acc.resize(b_cases.size());
    for (const auto& [bcnt, b_case_and_acc] :
         std::views::zip(b_cases, b_cases_acc) | std::views::enumerate) {
      const auto& [b_case, b_case_acc] = b_case_and_acc;
      b_case_acc.resize(b_case.size() + 1);
      b_case_acc[0] = 0;
      for (const auto i : std::views::iota(0, (int)b_case.size())) {
        b_case_acc[i + 1] = (b_case_acc[i] + b_case[i]) % kMod;
      }
    }
    lli ans = 0;
    std::vector<lli> case_sums(n, 0);
    for (const auto& [bcnt, b_case_and_acc] :
         std::views::zip(b_cases, b_cases_acc) | std::views::enumerate) {
      const auto& [b_case, b_case_acc] = b_case_and_acc;
      if (b_case.empty()) continue;
      // Fixing the range searches by `a[i]` forces `asum + value` to be
      // descending and consequently `lo` becomes ascending \o/.
      std::vector<std::vector<lli>::iterator> loits(a.size(), b_case.begin());
      auto endit = b_case.begin();
      for (const auto [asum, mask] : sum_by_mask) {
        // asum + bsum <= x - 1
        // bsum <= x - 1 - asum
        const lli hi = x - 1 - asum;
        if (*b_case.begin() > hi) continue;
        while (endit != b_case.end() && *endit <= hi) ++endit;
        const int r = (int)(endit - b_case.begin()) - 1;
        const int acnt = std::popcount((uint32_t)mask);
        lli& total_sum = case_sums[acnt + bcnt];
        for (uint32_t curr_mask = ~mask & all_mask; curr_mask != 0;
             curr_mask &= curr_mask - 1) {
          const int i = std::countr_zero(curr_mask);
          const lli value = a[i];
          // asum + value + bsum >= x
          // bsum >= x - value - asum
          const lli lo = x - value - asum;
          // Assuming `a` is descending, `lo` is ascending and we can break.
          if (b_case.back() < lo) break;
          auto& loit = loits[i];
          while (loit != b_case.end() && *loit < lo) ++loit;
          // loit = std::ranges::lower_bound(loit, endit, lo, std::less());

          const int l = (int)(loit - b_case.begin());
          // `lo` is increasing while `hi` is fixed. So, we can break.
          if (l > r) {
            break;
          }
          DEBUG std::println("\t\t\t{} {}", l, r);
          const lli case_sum =
              (((asum + value) % kMod) * (r - l + 1) % kMod +
               ((b_case_acc[r + 1] - b_case_acc[l]) % kMod + kMod) % kMod);
          total_sum = (total_sum + case_sum) % kMod;
        }
      }
    }
    for (const auto [total_cnt, case_sum] : case_sums | std::views::enumerate) {
      const lli p = pmemo[total_cnt];
      const lli to_add = case_sum * p % kMod;
      ans = (ans + to_add) % kMod;
    }
    DEBUG std::println("\t{}", ans);
    return ans;
  }

  lli Solve() {
    // return Naive();
    if (n <= 3) return Naive();
    lli ans = MeetInTheMiddle();
    std::swap(a, b);
    ans = (ans + MeetInTheMiddle()) % kMod;
    // assert(ans == Naive());
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> x)) return false;
    n2 = (n >> 1);
    banks.resize(n);
    for (lli& bi : banks) {
      std::cin >> bi;
    }
    std::ranges::sort(banks, std::greater());
    fat.resize(n + 1);
    fat[0] = 1;
    for (int i = 1; i <= n; ++i) fat[i] = (lli)i * fat[i - 1] % kMod;
    pmemo.resize(n);
    for (int i = 0; i < n; ++i)
      pmemo[i] = ModInv(fat[n]) * fat[n - i - 1] % kMod * fat[i] % kMod;

    for (int i = 0; i < n2; ++i) a.push_back(banks[i]);
    for (int i = n2; i < n; ++i) b.push_back(banks[i]);

    const lli ans = Solve();

    std::println("{}", ans);

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
