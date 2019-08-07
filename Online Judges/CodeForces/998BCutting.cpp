#include <bits/stdc++.h>
using namespace std;
int n, even[102], odd[102], inf = 1<<20;
int dp[101][101][101];

int solve(int a[], int i, int prev, int b)
{
  if (i == n)
  {
    if (even[n] - even[prev] != odd[n] - odd[prev]) return(-inf);
    return(0);
  }
  if (b < 0) return(-inf);

  if (dp[i][b][prev] == -1)
  {
    int ans = solve(a, i + 1, prev, b);
    if (even[i] - even[prev] == odd[i] - odd[prev])
      ans = max(ans, 1 + solve(a, i + 1, i, b - abs(a[i] - a[i - 1])));
    dp[i][b][prev] = ans;
  }

  return(dp[i][b][prev]);
}

int main()
{
  int b; scanf("%d %d", &n, &b);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  even[0] = odd[0] = 0;
  for (int i = 0; i < n; i ++)
  {
    even[i + 1] = even[i] + !(a[i] & 1);
    odd[i + 1] = odd[i] + (a[i] & 1);
  }

  memset(dp, -1, sizeof(dp));
  int ans = solve(a, 1, 0, b);
  printf("%d\n", ans < 0 ? 0 : ans);

  return(0);
}