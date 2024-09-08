#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
A and B are compatible if A|B = A+B
A|B = A+B -> A&B = 0
g(a, b) = true if a compatible with b

solution = f(x) = sum(y in A where g(x, y) is true)

~A is compatible with A
subset(x) = every y where x & y = y
  e.g. subset(101) = [000, 001, 100, 101]
  We can build and compute the sum of this subset in 3^n using SOS DP.
f(x) = sum(subset(~x) in A)
*/

const int kMaxBit = 19;
const int kAllowedBits = (1 << (kMaxBit + 1)) - 1;
const int kMaxA = kAllowedBits;

struct TestCase {

  int n;
  vector<int> a;
  vector<int> cnt;
  int q;

  vector<lli> memo;
  void Precompute() {
    memo.resize(kMaxA + 1, 0);
    for (int i = 1; i <= kMaxA; ++i) {
      for (int j = i; j > 0; j = (j - 1) & i) {
        memo[i] += cnt[j] * j;
      }
    }
  }

  lli Solve(int x) {
    const int target = ~x & kAllowedBits;
    lli& ans = memo[target];
    if (ans != -1) return ans;

    ans = 0;
    for (int j = target; j > 0; j = (j - 1) & target) {
      ans += (lli)cnt[j] * j;
    }
    return ans;
  }

  void Run() {
    scanf("%d", &n);
    a.resize(n), cnt.resize(kMaxA + 1, 0);
    for (int& aa : a) {
      scanf("%d", &aa);
      ++cnt[aa];
    }

    memo.resize(kMaxA + 1, -1);
    // Precompute();

    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
      int x;
      scanf("%d", &x);
      printf("%lld\n", Solve(x));
    }
  }
};

int main() {
  TestCase test_case;
  test_case.Run();

  return 0;
}
