#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int

/*
Ignore the `2^n` sets of colors and let's find a solution for a single set:
  Given `n` colors with `A[i]` balls per color `i`. Find the minimum number of
  groups where each group should contain at most 2 balls and no repeated color.

There are only 2 cases:
  If max(A) > (sum(A) / 2): max(A)
  else: ceil(sum(A) / 2)
  In other words, you can always divide in 2 except when one color is more
  frequent than all the rest.

Back to the 2^n sets, using DP we can iterate through all sets. And if we sort
`A` ascending, every position `i` will become the new maximum of that set.
So, the DP just needs to maintain `i` and `sum` for us to find the answer for
each set in O(1). Leading to a final complextiy of O(n*sum) \o/.
*/

const int kMod = 998244353;
const int kMaxA = 5e3;

struct TestCase {
  int n;
  std::vector<int> a;

  lli Naive(int i = 0, int sum = 0, int maxi = 0) {
    if (i == n) {
      return maxi > (sum >> 1) ? maxi : ((sum + 1) >> 1);
    }
    return (Naive(i + 1, sum, maxi) +
            Naive(i + 1, sum + a[i], std::max(maxi, a[i]))) %
           kMod;
  }

  std::vector<std::array<int, kMaxA + 1>> memo;
  int Solve(int i = 0, int sum = 0) {
    if (i == n) {
      return 0;
    }
    int& ans = memo[i][sum];
    if (ans != -1) return ans;

    ans = (Solve(i + 1, sum) + Solve(i + 1, sum + a[i])) % kMod;
    sum += a[i];
    if (a[i] > (sum >> 1)) {
      ans = (ans + a[i]) % kMod;
    } else {
      ans = (ans + ((sum + 1) >> 1)) % kMod;
    }

    return ans;
  }
  
  int SolveTopDown() {
    memo.resize(n);
    for (auto& memoi : memo) std::ranges::fill(memoi, -1);
    const int ans = Solve();
    return ans;
  }

  int SolveBottomUp() {
    memo.resize(n + 1);
    std::ranges::fill(memo[n], 0);
    for (int i = n - 1; i >= 0; --i) {
      for (int s = kMaxA - a[i]; s >= 0; --s) {
        int& ans = memo[i][s];
        ans = (memo[i + 1][s] + memo[i + 1][s + a[i]]) % kMod;
        if (a[i] > ((s + a[i]) >> 1)) {
          ans = (ans + a[i]) % kMod;
        } else {
          ans = (ans + ((s + a[i] + 1) >> 1)) % kMod;
        }
      }
    }
    return memo[0][0];
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    for (int& ai : a) std::cin >> ai;
    std::ranges::sort(a, std::less());

    // const int ans = SolveTopDown();
    const int ans = SolveBottomUp();
    std::println("{}", ans);
    DEBUG {
      const lli naive = Naive();
      std::println("naive: {}", naive);
    }

    return true;
  }
};

int main() {
  // std::println("{}", (kMod)*2 <= std::numeric_limits<int>::max());
  while (true) {
    TestCase test_case;
    if (!test_case.Run()) break;
    // break;
  }

  return 0;
}