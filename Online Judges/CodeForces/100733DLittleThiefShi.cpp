#include <bits/stdc++.h>
using namespace std;
#define lli long long int
int v[(int) 1e6], n;
lli dp[(int) 1e6];

lli solve(int i)
{
  if (i >= n) return(0);
  if (dp[i] == -1) dp[i] = max(solve(i + 1), solve(i + 3) + v[i]);
  return(dp[i]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  scanf("%d", &n); for (int i = 0; i < n; i ++) scanf("%d", &v[i]);
  lli ans = solve(0);
  printf("%lld\n", ans);
  return(0);
}