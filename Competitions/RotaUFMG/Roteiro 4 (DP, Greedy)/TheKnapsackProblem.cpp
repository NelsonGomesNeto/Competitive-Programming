#include <bits/stdc++.h>
using namespace std;
int dp[2001][2001];

int knapsack(int item[][2], int i, int s)
{
  if (i < 0) return(0);

  if (dp[i][s] == -1)
  {
    int best = knapsack(item, i - 1, s);
    if (s - item[i][0] >= 0)
      best = max(best, knapsack(item, i - 1, s - item[i][0]) + item[i][1]);
    dp[i][s] = best;
  }
  return(dp[i][s]);
}

int main()
{
  int s, n; scanf("%d %d", &s, &n);
  int item[n][2];
  for (int i = 0; i < n; i ++)
    scanf("%d %d", &item[i][0], &item[i][1]);

  memset(dp, -1, sizeof(dp));
  int best = knapsack(item, n - 1, s);
  printf("%d\n", best);
  return(0);
}