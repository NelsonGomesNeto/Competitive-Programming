  #include <bits/stdc++.h>
  using namespace std;
  int dp[50001], m, n, smallest = 1<<20;

  void coinChange(int coin[])
  {
    dp[0]= 0;
    for (int i = smallest; i <= m; i ++)
    {
      dp[i] = 1<<20;
      for (int j = 0; j < n; j ++)
        if (i - coin[j] >= 0 && dp[i - coin[j]] != -1)
          dp[i] = min(dp[i], 1 + dp[i - coin[j]]);
    }
  }

  int main()
  {
    while (scanf("%d", &m) && m)
    {
      scanf("%d", &n);
      int coin[n]; memset(dp, -1, sizeof(dp));
      for (int i = 0; i < n; i ++)
      {
        scanf("%d", &coin[i]);
        dp[coin[i]] = 1; smallest = min(smallest, coin[i]);
      }

      coinChange(coin);
      if (dp[m] == 1<<20)
        printf("Impossivel\n");
      else
        printf("%d\n", dp[m]);
    }
    return(0);
  }