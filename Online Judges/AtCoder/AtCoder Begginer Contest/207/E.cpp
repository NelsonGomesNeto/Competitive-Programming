#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3; int n;
const lli mod = 1e9 + 7;
lli a[maxN];
lli acc[maxN + 1];
vector<int> next[maxN][maxN];

lli memo[maxN + 5][maxN + 5], pmemo[maxN + 5][maxN + 5];
lli solve(int i, int d);
lli pref(int i, int j, int d)
{
  if (j == n) return 0;
  lli &ans = pmemo[i][d];
  if (ans != -1) return ans;
  ans = pref(i, j + 1, d);
  if ((acc[j + 1] - acc[i]) % d == 0)
    ans = (ans + solve(j + 1, d + 1)) % mod;
  return ans;
}
lli solve(int i = 0, int d = 1)
{
  if (i == n) return 1;
  lli &ans = memo[i][d];
  if (ans != -1) return ans;

  // ans = pref(i, i, d);
  ans = 0;
  for (int j = i; j < n; j++)
    if ((acc[j + 1] - acc[i]) % d == 0)
      ans = (ans + solve(j + 1, d + 1)) % mod;

  return ans;
}

lli solve2()
{
  memset(memo, 0, sizeof(memo));
  for (int i = 1; i <= n + 1; i++) memo[n][i] = 1;

  for (int i = n - 1; i >= 0; i--)
    for (int j = n - 1; j >= i; j--)
      for (int d = 1; d <= n; d++)
        if ((acc[j + 1] - acc[i]) % d == 0)
          memo[i][d] = (memo[i][d] + memo[j + 1][d + 1]) % mod;

  return memo[0][1];
}

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

int main()
{
  int tt = 0;
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      acc[i + 1] = acc[i] + a[i];
    }

    memset(memo, -1, sizeof(memo));
    memset(pmemo, -1, sizeof(pmemo));
    lli ans = solve();
    lli ans2 = solve2();
    printf("%lld %lld\n", ans, ans2);
  }
  return 0;
}