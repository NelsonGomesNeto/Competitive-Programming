#include <bits/stdc++.h>
using namespace std;
int dp[21][201];

int knapsack(int items[][20], int i, int budget)
{
  //printf("%d %d\n", i, items[i][0]);
  if (i < 0) return(0);

  if (dp[i][budget] == -1)
  {
    int best = 0;
    for (int j = 1; j <= items[i][0]; j ++)
      if (budget - items[i][j] >= 0)
        best = max(best, knapsack(items, i - 1, budget - items[i][j]) + items[i][j]);
    dp[i][budget] = best;
  }
  return(dp[i][budget]);
}

int main()
{
  int n; scanf("%d", &n);
  while (n --)
  {
    int budget, c; scanf("%d %d", &budget, &c);
    int items[c][20], cheapest = 0;
    for (int i = 0; i < c; i ++)
    {
      int k, cc = 1<<20; scanf("%d", &k); items[i][0] = k;
      for (int j = 0; j < k; j ++)
      {
        scanf("%d", &items[i][j + 1]);
        cc = min(cc, items[i][j + 1]);
      }
      cheapest += cc;
    }

    if (cheapest > budget)
      printf("no solution\n");
    else
    {
      memset(dp, -1, sizeof(dp));
      printf("%d\n", knapsack(items, c - 1, budget));
    }
  }
  return(0);
}