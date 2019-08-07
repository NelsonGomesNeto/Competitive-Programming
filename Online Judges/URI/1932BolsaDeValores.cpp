#include <bits/stdc++.h>
using namespace std;
int n, c, dp[200001][2];

int solve(int cot[], int i, int b)
{
  if (i == n) return(0);
  if (dp[i][b] == -1)
  {
    int ans = solve(cot, i + 1, b);
    if (!b) ans = max(ans, solve(cot, i + 1, 1) - cot[i] - c);
    if (b) ans = max(ans, cot[i] + solve(cot, i + 1, 0));
    dp[i][b] = ans;
  }
  return(dp[i][b]);
}

int main()
{
  scanf("%d %d", &n, &c);
  int cot[n]; for (int i = 0; i < n; i ++) scanf("%d", &cot[i]);

  memset(dp, -1, sizeof(dp));
  int ans = solve(cot, 0, 0);
  printf("%d\n", ans);
  return(0);
}
