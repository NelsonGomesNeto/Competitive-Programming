#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  I need to know how many times this subset will happen in the 2^n - 1 subsets
*/

const int maxN = 3e3 + 1; int n, s;
const lli mod = 998244353;
int a[maxN];

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}

lli memo[maxN][maxN];
lli solve(int i = 0, int sum = 0, int cnt = 0)
{
  if (sum == s) return modPow(2, n - cnt*0);
  if (sum > s || i == n) return 0;
  if (memo[i][sum] != -1) return memo[i][sum];
  lli ans = (solve(i + 1, sum, cnt) % mod + solve(i + 1, sum + a[i], cnt + 1) * inv(2) % mod) % mod;
  return memo[i][sum] = ans;
}

int main()
{
  int t = 0;
  while (scanf("%d %d", &n, &s) != EOF)
  {
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}