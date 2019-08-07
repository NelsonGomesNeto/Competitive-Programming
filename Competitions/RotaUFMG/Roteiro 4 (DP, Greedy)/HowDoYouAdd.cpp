#include <bits/stdc++.h>
#define lli long long int
lli dp[100][101], mod = 1e6;

lli solve(int n, int k, int sum)
{
  if (k == -1) return(n == sum);

  if (dp[k][sum] == -1)
  {
    lli ans = 0;
    for (int i = 0; i <= n && sum + i <= n; i ++)
      ans += solve(n, k - 1, sum + i) % mod;
    dp[k][sum] = ans % mod;
  }
  return(dp[k][sum]);
}

int main()
{
  int n, k;
  while (scanf("%d %d", &n, &k) && !(!n && !k))
  {
    memset(dp, -1, sizeof(dp));
    lli ans = solve(n, k - 1, 0);
    printf("%lld\n", ans);
  }
}