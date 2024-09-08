#include <bits/stdc++.h>
using namespace std;
int dp[50][1001];

int knapsack(int card[][2], int i, int capacity)
{
  if (i == -1) return(0);

  if (dp[i][capacity] == -1)
  {
    int ans = knapsack(card, i - 1, capacity);
    if (capacity - card[i][0] >= 0)
      ans = max(ans, card[i][1] + knapsack(card, i - 1, capacity - card[i][0]));
    dp[i][capacity] = ans;
  }
  return(dp[i][capacity]);
}

int main()
{
  int capacity, n, t = 0;
  while (scanf("%d %d", &capacity, &n) && !(!capacity && !n))
  {
    memset(dp, -1, sizeof(dp));
    int card[n][2];
    for (int i = 0; i < n; i ++)
      scanf("%d %d", &card[i][0], &card[i][1]);

    int sorry = knapsack(card, n - 1, capacity);
    printf("Teste %d\n%d\n\n", ++ t, sorry);
  }
  return(0);
}