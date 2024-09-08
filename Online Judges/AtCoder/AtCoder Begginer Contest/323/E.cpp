#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;
lli ModPow(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli ModInv(lli x) {
  return ModPow(x, mod - 2);
}

const int kMaxN = 1e3, kMaxX = 1e4;
int n, x;
int t[kMaxN];

double Solve2(int curr = 0) {
  double p = (double)1 / n;
  if (curr <= x && curr + t[0] > x) {
    return p;
  }

  if (curr >= x) return 0;

  double ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += p * Solve2(curr + t[i]);
  }
  return ans;
}

lli prob;
lli memo[kMaxX + 1];
lli Solve(int curr = 0, int last_played = -1) {
  if (last_played == 0 && curr > x && curr - t[0] <= x) {
    return 1;
  }
  if (curr > x) return 0;
  // if (curr + t[0] > x) {
  //   return prob;
  // }
  assert(curr <= x);

  lli& ans = memo[curr];
  if (ans != -1) return ans;

  ans = 0;
  for (int i = 0; i < n; ++i) {
    lli res = prob * Solve(curr + t[i], i) % mod;
    ans = (ans + res) % mod;
  }
  return ans;
}

int main() {
  while (~scanf("%d %d", &n, &x)) {
    for (int i = 0; i < n; ++i)
      scanf("%d", &t[i]);

    memset(memo, -1, sizeof(memo));
    prob = ModInv(n);
    lli ans = Solve();
    printf("%lld\n", ans);
  }
  return 0;
}
