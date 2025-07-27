#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (1)
#define lli long long int
#define ldouble long double

/*
This problem is incredible, but very tricky. Before attempting to solve it, try
to explore what causes the number of attempts to increase when you increase n or
k.

Here are some rough findings:
k = 1 -> n tests
k = 2 -> min j where ApSum(1, j) >= n
k = 3 -> I'm not sure yet, but the division point follows an Ap as well
  Like: 1, 3, 6, 10, 15
         +2 +3 +4  +5
  Following those division points, we should be able to reconstruct the
  correct number of attempts.

But no, I'm afraid these patterns won't help much other than confirm that the
even for k = 2, the maximum number of attempts is O(sqrt(n)).

The killer hint is to try to find the boundaries. For example, with n and k
you need x attempts but there is an N > n for which you'll need exactly x + 1
attempts. Conversely, all n <= m < N will have exactly x attempts.
That will allow you to optimize the O(n*k) DP to O(sqrt(n)*k) on both time and
memory. I couldn't come-up with a TopDown way of computing this.

Maybe TopDown works if we ask it to compute something else instead of the
answer directly?
*/

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& arr) {
  out << "{";
  bool first = true;
  for (const auto v : arr) {
    if (!first) out << ", ";
    first = false;
    out << v;
  }
  out << "}";
  return out;
}
template <class T>
std::string ToString(const std::vector<T>& arr) {
  std::ostringstream sout;
  sout << arr;
  return sout.str();
}

// In the best worst case, we need 30 attempts to verify 1e9 ballons
// So, k > 30 is a waste
const lli kMaxK = 30;

struct TestCase {
  lli n, k;

  std::vector<std::vector<lli>> max_reachable_n;
  int GetMaxAttemps(const lli curr_n, const lli curr_k) {
    if (curr_n == 0) return 0;
    if (curr_k == 1) return curr_n;
    const std::vector<lli>& max_reachable_n_at_k = max_reachable_n[curr_k];
    const auto it = std::lower_bound(max_reachable_n_at_k.begin(),
                                     max_reachable_n_at_k.end(), curr_n);
    // if (it == max_reachable_n_at_k.end()) {
    //   std::println("\t\tGetMaxAttempts({}, {}) = {}", curr_n, curr_k,
    //                ToString(max_reachable_n_at_k));
    //   std::fflush(stdout);
    // }
    assert(it != max_reachable_n_at_k.end());
    return std::distance(max_reachable_n_at_k.begin(), it);
  }
  bool lol = false;
  int GetAttempts(const lli n_limit, const lli curr_k, const lli split) {
    const int left = GetMaxAttemps(split - 1, curr_k - 1);
    const int right = GetMaxAttemps(n_limit - split, curr_k);
    // if (lol)
    //   std::println("\t\t\tGetAttempts({}, {}, {}) = {} {}", n_limit, curr_k,
    //                split, left, right);
    const int attempts = 1 + std::max(left, right);
    return attempts;
  }
  lli BinarySearch(lli lo, lli hi, const bool upper_bound, const int target,
                   const std::function<int(lli)>& Eval) {
    // DEBUG2 if (upper_bound) {
    //   std::println("\tBinarySearch({}, {}, {}) = [{} : {}]", lo, hi, target,
    //                Eval(lo), Eval(hi));
    //   lol = true;
    //   std::println("\t\tEval({}) = {}", lo, Eval(lo));
    //   if (lo < hi) std::println("\t\tEval({}) = {}", hi - 1, Eval(hi - 1));
    //   std::println("\t\tEval({}) = {}", hi, Eval(hi));
    //   lol = false;
    // }
    while (lo < hi) {
      const lli mid = (lo + hi + upper_bound) >> 1;
      if (upper_bound) {
        if (Eval(mid) <= target)
          lo = mid;
        else
          hi = mid - 1;
      } else {
        if (Eval(mid) >= target)
          hi = mid;
        else
          lo = mid + 1;
      }
    }
    // DEBUG2 if (upper_bound) { std::println("\t\tnext_break_point: {}", lo); }
    return lo;
  }
  void PrecalcBinarySearch() {
    max_reachable_n.resize(k + 1, {0});
    for (lli curr_k = 2; curr_k <= k; ++curr_k) {
      lli prv_break_point = 1;
      std::vector<lli>& max_reachable_n_at_k = max_reachable_n[curr_k];
      for (lli curr_n = 1; curr_n <= n;) {
        // Here we want to find:
        // 1. The smallest `n` such that it requires at least 1 extra attempt;
        //    * `GetMaxAttempts` relies on `max_reachable_n`, so the biggest
        //      attempt on the range will have exactly 1 extra attempt.
        //    * AFAICT, in the BinarySearch for `next_n` below, it starts with
        //      the left side (k - 1) costing more attempts and ends with the
        //      rigth side (same k) costing more attempts.
        //    * Note that on this search we're fixing the `slice` so the left
        //      side won't grow but the right side will and also.
        // 2. The biggest `split` point such that it requires 1 extra attempt.

        const lli next_n =
            BinarySearch(curr_n, max_reachable_n_at_k.back() + prv_break_point,
                         /*upper_bound=*/false, max_reachable_n_at_k.size(),
                         [this, curr_k, prv_break_point](const lli n_limit) {
                           return GetAttempts(n_limit, curr_k, prv_break_point);
                         });
        assert(next_n == max_reachable_n_at_k.back() + prv_break_point);
        assert(GetAttempts(next_n, curr_k, prv_break_point) >=
               (int)max_reachable_n_at_k.size());

        prv_break_point = BinarySearch(
            prv_break_point,
            curr_k == 2 ? next_n : max_reachable_n[curr_k - 1].back() + 1,
            /*upper_bound=*/true, max_reachable_n_at_k.size(),
            [this, next_n, curr_k](const lli split) {
              return GetAttempts(next_n, curr_k, split);
            });

        max_reachable_n_at_k.back() = next_n - 1;
        max_reachable_n_at_k.push_back(next_n);

        curr_n = next_n + 1;
      }
    }
    // DEBUG for (int i = 1; i <= n; ++i) {
    //   std::println("Solve({}, {}) = {}", i, k, GetMaxAttemps(i, k));
    // }
    // DEBUG for (int curr_k = 1; curr_k <= k; ++curr_k) {
    //   std::println("Precalc({}, {}) = {} | max_reachable = ({}) {}", n,
    //   curr_k,
    //                GetMaxAttemps(n, curr_k), max_reachable_n[curr_k].size(),
    //                ToString(max_reachable_n[curr_k]));
    // }
  }
  void PrecalcO1() {
    max_reachable_n.resize(k + 1, {0});
    for (lli curr_k = 2; curr_k <= k; ++curr_k) {
      lli prv_break_point = 1;
      int prv_break_point_index = 0;
      std::vector<lli>& max_reachable_n_at_prv_k = max_reachable_n[curr_k - 1];
      std::vector<lli>& max_reachable_n_at_k = max_reachable_n[curr_k];
      for (lli curr_n = 1; curr_n <= n;) {
        // Here we want to find:
        // 1. The smallest `n` such that it requires exactly 1 extra attempt;
        // 2. The biggest `split` point such that it requires 1 extra attempt.

        // `GetAttempts` is computed through:
        // 1 + std::max(
        //       GetMaxAttempts(split - 1, k - 1), GetMaxAttempts(n - split, k))
        // So, the left side will have exactly `prv_break_point-1` and the
        // right side will have exactly `max_reachable_n_at_k.back()` which will
        // force the right side to `max_reachable_n_at_k.size()-1` (last
        // position). And the left side will also be `prv_break_point_index`
        // which at this point is exactly `max_reachable_n_at_k.size()-1` as
        // well since we increase `prv_break_point_index` on every iteration.
        const lli next_n = max_reachable_n_at_k.back() + prv_break_point;
        assert(GetAttempts(next_n, curr_k, prv_break_point) ==
               (int)max_reachable_n_at_k.size());

        // Similarly, we want to advance to the next break point.
        prv_break_point =
            curr_k == 2 ? std::min(curr_n, prv_break_point + 1)
                        : max_reachable_n_at_prv_k[prv_break_point_index] + 1;
        ++prv_break_point_index;
        assert(GetAttempts(next_n, curr_k, prv_break_point) ==
               (int)max_reachable_n_at_k.size());

        max_reachable_n_at_k.back() = next_n - 1;
        max_reachable_n_at_k.push_back(next_n);

        curr_n = next_n + 1;
      }
    }
    // DEBUG for (int i = 1; i <= n; ++i) {
    //   std::println("Solve({}, {}) = {}", i, k, GetMaxAttemps(i, k));
    // }
    // DEBUG for (int curr_k = 1; curr_k <= k; ++curr_k) {
    //   std::println("Precalc({}, {}) = {} | max_reachable = ({}) {}", n,
    //   curr_k,
    //                GetMaxAttemps(n, curr_k), max_reachable_n[curr_k].size(),
    //                ToString(max_reachable_n[curr_k]));
    // }
  }

  bool Run() {
    if (!(std::cin >> n >> k)) return false;

    k = std::min(k, kMaxK);

    PrecalcO1();
    // std::println("{}", GetMaxAttemps(n, k));
    std::cout << GetMaxAttemps(n, k) << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
