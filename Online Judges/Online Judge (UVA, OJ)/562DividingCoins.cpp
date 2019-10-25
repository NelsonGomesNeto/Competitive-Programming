#include <bits/stdc++.h>
using namespace std;
int coins[100];
int dp[100][500 * 100 + 1];

int solve(int i, int capacity)
{
  if (i < 0) return(0);
  if (dp[i][capacity] == -1)
  {
    int ans = solve(i - 1, capacity);
    if (capacity - coins[i] >= 0)
      ans = max(ans, solve(i - 1, capacity - coins[i]) + coins[i]);
    dp[i][capacity] = ans;
  }
  return(dp[i][capacity]);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    int total = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &coins[i]);
      total += coins[i];
    }

    memset(dp, -1, sizeof(dp));
    int left = total - solve(n - 1, ceil((double) total / 2));
    int ans = abs(total - left - left);
    printf("%d\n", ans);
  }
  return(0);
}