#include <bits/stdc++.h>
int k, l, n;

int bottomUp(int coins, int dp[])
{
  int at = 1; dp[0] = 0;
  for (int i = 1; i <= coins; i ++, at = 1 - at)
  {
    dp[i] = 0;
    if (i - 1 >= 0 && !dp[i - 1]) dp[i] = 1;
    if (i - k >= 0 && !dp[i - k]) dp[i] = 1;
    if (i - l >= 0 && !dp[i - l]) dp[i] = 1;
  }
  return(0);
}

int main()
{
  scanf("%d %d %d", &k, &l, &n);
  int dp[(int) 1e6 + 1];
  bottomUp(1e6, dp);
  while (n --)
  {
    int coins; scanf("%d", &coins);
    printf("%c", dp[coins] ? 'A' : 'B');
  } printf("\n");
  return(0);
}