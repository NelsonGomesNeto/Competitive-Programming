#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const lli kInf = 1e10;

/*
(x [0 : M - 1]) sum((i [1 : N]) min(x ^ A[i]))

for each bit
freq(bit[i]) * (All(A[i] has bit bit[i]) ? 0 : 1)

for each bit
  do I have in A, numbers with bits >= bit?
  get the smallest of them is it <= M - 1?
  bits until bit are fixed
  then we can make any number up to M - 1 with the remaining bits

  If I already processed this prefix, I can't do it again
*/

int N;
lli M, target;
int msb_of_target, msb_of_a;
std::vector<lli> A;
struct TestCase {
  int FindFirstOne(int lo, int hi, const int bit) {
    const lli mask = 1LL << bit;
    while (lo < hi) {
      const int mid = (lo + hi) >> 1;
      if (A[mid] & mask)
        hi = mid;
      else
        lo = mid + 1;
    }
    return (A[lo] & mask) ? lo : N;
  }

  lli Naive() {
    lli ans = 0;
    for (lli x = 0; x < M; ++x) {
      lli minimum = std::numeric_limits<lli>::max();
      for (const auto ai : A) minimum = std::min(minimum, x ^ ai);
      ans += minimum;
      std::println("\tx {} | minimum {}", x, minimum);
    }
    return ans;
  }

  std::map<std::tuple<int, int, int, bool>, lli> memo;
  lli Solve(const lli pref = 0, const int lo = 0, const int hi = N - 1,
            const int bit = msb_of_target, const bool equal = true) {
    if (bit == -1) {
      return pref;
    }
    const lli mask = 1LL << bit;

    // const auto curr = std::tuple<int, int, int, bool>{lo, hi, bit, equal};
    // auto it = memo.find(curr);
    // if (it != memo.end()) return it->second;

    lli ans = 0;
    // I need to handle 2 things:
    // * get hid of this `pref`
    //   * also return a count and then multiply every `pref` by count.
    //   * (probably easier) another alternative is moving this computation to
    //   the end.
    //   * actually, it can change the `equal` part. So we can't easily move it
    //   to the end.
    // * handle cases where msb_of_a > msb_of_target
    if (bit > msb_of_a) {
      std::println("\t\t{} {} {:b}", bit, equal, target & mask);
      if (equal) {
        if (target & mask)
          ans = Solve(pref, lo, hi, bit - 1, false) +
                (0 + Solve(pref + mask, lo, hi, bit - 1, true));
        else
          ans = Solve(pref, lo, hi, bit - 1, true);
      } else {
        ans = Solve(pref, lo, hi, bit - 1, false) +
              (0 + Solve(pref + mask, lo, hi, bit - 1, false));
      }
    } else if (lo == hi) {
      if (A[lo] & mask) {
        if (equal) {
          if (target & mask)
            ans = Solve(pref, lo, hi, bit - 1, true) +
                  (mask + Solve(pref, lo, hi, bit - 1, false));
          else
            ans = (mask + Solve(pref, lo, hi, bit - 1, true));
        } else {
          ans = Solve(pref, lo, hi, bit - 1, false) +
                (mask + Solve(pref, lo, hi, bit - 1, false));
        }
      } else {
        if (equal) {
          if (target & mask)
            ans = (mask + Solve(pref, lo, hi, bit - 1, true)) +
                  Solve(pref, lo, hi, bit - 1, false);
          else
            ans = Solve(pref, lo, hi, bit - 1, true);
        } else {
          ans = (mask + Solve(pref, lo, hi, bit - 1, false)) +
                Solve(pref, lo, hi, bit - 1, false);
        }
      }
    } else {
      const int first_one_pos = FindFirstOne(lo, hi, bit);
      if (first_one_pos == lo) {
        // All ones
        if (equal) {
          if (target & mask)
            ans = Solve(pref, lo, hi, bit - 1, true);
          else
            ans = 0;
        } else {
          ans = Solve(pref, lo, hi, bit - 1, false);
        }
      } else if (first_one_pos == N) {
        // All zeroes
        if (equal) {
          if (target & mask)
            ans = Solve(pref, lo, hi, bit - 1, false);
          else
            ans = Solve(pref, lo, hi, bit - 1, true);
        } else {
          ans = Solve(pref, lo, hi, bit - 1, false);
        }
      } else {
        // Mix
        if (equal) {
          if (target & mask)
            ans = Solve(pref, lo, first_one_pos - 1, bit - 1, false) +
                  Solve(pref, first_one_pos, hi, bit - 1, true);
          else
            ans = Solve(pref, lo, first_one_pos - 1, bit - 1, true);
        } else {
          ans = Solve(pref, lo, first_one_pos - 1, bit - 1, false) +
                Solve(pref, first_one_pos, hi, bit - 1, false);
        }
      }
    }
    DEBUG { std::println("\t{} | {} {} | {} | {}", bit, lo, hi, equal, ans); }
    // memo.insert_or_assign(curr, ans);
    return ans;
  }

  bool Run() {
    if (!(std::cin >> N >> M)) return false;
    // if (N > 6) return false;
    target = M - 1;
    A.resize(N);
    for (auto& ai : A) std::cin >> ai;
    std::sort(A.begin(), A.end());
    for (int bit = 29; bit >= 0; --bit) {
      if (target & (1LL << bit)) {
        msb_of_target = bit;
        break;
      }
    }
    for (int bit = 29; bit >= 0; --bit) {
      if (A.back() & (1LL << bit)) {
        msb_of_a = bit;
        break;
      }
    }

    // Make a search and try to build each number during the search;
    const lli ans = Solve();
    std::cout << ans << "\n";
    const lli naive_ans = Naive();
    std::cout << "naive_ans: " << naive_ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

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
