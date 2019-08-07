#include <bits/stdc++.h>
using namespace std;
int dp[101][5000 + 1];

int subsetSum(int value[], int i, int sum)
{
  if (i == -1) return(0);

  if (dp[i][sum] == -1)
  {
    int ans = subsetSum(value, i - 1, sum);
    if (sum - value[i] >= 0)
      ans = max(ans, value[i] + subsetSum(value, i - 1, sum - value[i]));
    dp[i][sum] = ans;
  }
  return(dp[i][sum]);
}

int bottomUp(int value[], int n, int target)
{
  for (int i = 0; i <= n; i ++)
    for (int j = 0; j <= target; j ++)
      if (!i || !j)
        dp[i][j] = 0;
      else if (value[i - 1] <= j)
        dp[i][j] = max(value[i - 1] + dp[i - 1][j - value[i - 1]], dp[i - 1][j]);
      else
        dp[i][j] = dp[i - 1][j];
  return(dp[n][target]);
}

int main()
{
  int x, y, n, t = 0;
  while (scanf("%d %d %d", &x, &y, &n) && !(!x && !y && !n))
  {
    if (t ++) printf("\n");
    int value[n], sum = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &value[i]);
      sum += value[i];
    }

    int target = (max(x, y) + sum - min(x, y)) / 2, can = 0;
    if (!((max(x, y) + sum - min(x, y)) & 1))
    {
      //memset(dp, -1, sizeof(dp));
      //can = subsetSum(value, n - 1, target) == target;
      can = bottomUp(value, n, target) == target;
    }
    printf("Teste %d\n%s\n", t, can ? "S" : "N");
  }
  return(0);
}
//sum * (max(x, y) + sum - min(x, y)) / (2 * sum)