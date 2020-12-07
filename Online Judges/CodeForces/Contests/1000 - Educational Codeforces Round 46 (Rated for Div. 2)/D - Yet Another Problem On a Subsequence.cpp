#include <bits/stdc++.h>
using namespace std;
#define lli long long int
int valid[1000][1000], n;
lli dp[1000][1000], mod = 998244353;

lli solve(int i, int j)
{
  if (i >= j) return(0);

  if (dp[i][j] == -1)
  {
    lli ans = valid[i][j];
    int mid = (i + j) / 2;
    lli a = solve(i, mid);
    lli b = solve(mid + 1, j);
    if (a && b)
      ans ++;
    ans += a + b;
    dp[i][j] = ans;
  }
  return(dp[i][j]);
}

int main()
{
  scanf("%d", &n);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);

  memset(valid, 0, sizeof(valid));
  for (int i = 0; i < n; i ++)
    if (a[i] > 0)
    {
      int j = a[i] + i;
      // printf("%d %d %d\n", i, j, a[i]);
      while (j < n)
      {
        valid[i][j] ++;
        j ++;
      }
    }

  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      printf("%d%c", valid[i][j], j < n - 1 ? ' ' : '\n');

  memset(dp, -1, sizeof(dp));
  lli ans = solve(0, n - 1);
  printf("%lld\n", ans);

  return(0);
}