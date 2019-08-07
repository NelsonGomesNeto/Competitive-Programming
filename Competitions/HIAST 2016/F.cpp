#include <bits/stdc++.h>
using namespace std;
int n, v[100];
int dp[100][201], inf = 1<<20;

int solve(int i, int diff)
{
  if (diff > 200 || diff < 0) return(inf);
  if (i == n) return(-1);
  if (dp[i][diff] == -1)
  {
    int now = abs(diff - 100);
    int a = max(now, solve(i + 1, diff + v[i]));
    int b = max(now, solve(i + 1, diff - v[i]));
    dp[i][diff] = min(a, b);
  }
  return(dp[i][diff]);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &v[i]);
    memset(dp, -1, sizeof(dp));
    printf("%d\n", solve(0, 100));
  }
  return(0);
}
