#include <bits/stdc++.h>
#define lli long long int
lli mod = (lli) 1e9 + 7;

lli dp[50 + 1][(int) 1e5 + 1];

lli solve(int i, int t, int m, int n)
{
  if (t == 0) return(1);

  if (dp[t][i] == -1)
  {
    lli ways = 0;
    if (i + 1 <= n)
      ways = (ways + solve(i + 1, t - 1, m, n)) % mod;
    if (i - 1 >= m)
      ways = (ways + solve(i - 1, t - 1, m, n)) % mod;
    dp[t][i] = ways;
  }

  return(dp[t][i]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  int t, m, n; scanf("%d %d %d", &t, &m, &n);

  lli ans = 0;
  for (int i = m; i <= n; i ++)
    ans = (ans + solve(i, t - 1, m, n)) % mod;

  printf("%lld\n", ans);

  return(0);
}