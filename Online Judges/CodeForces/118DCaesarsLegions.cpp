#include <bits/stdc++.h>
#define lli long long int
lli mod = 100000000;
lli dp[101][101][11][11];
int n1, n2, k1, k2;

lli solve(int i, int end, int l1, int l2, int has1, int has2)
{
  if (l1 > k1 || l2 > k2 || has1 < 0 || has2 < 0) return(0);
  if (i == end) return(1);

  if (dp[has1][has2][l1][l2] == -1)
  {
    lli r1 = solve(i + 1, end, l1 + 1, 0, has1 - 1, has2) % mod;
    lli r2 = solve(i + 1, end, 0, l2 + 1, has1, has2 - 1) % mod;
    dp[has1][has2][l1][l2] = (r1 + r2) % mod;
  }
  return(dp[has1][has2][l1][l2]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  scanf("%d %d %d %d", &n1, &n2, &k1, &k2);
  lli ans = solve(0, n1 + n2, 0, 0, n1, n2);
  printf("%lld\n", ans);

  return(0);
}
