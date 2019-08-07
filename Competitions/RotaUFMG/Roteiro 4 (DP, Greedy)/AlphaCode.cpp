#include <bits/stdc++.h>
#define lli long long int

lli solve(char s[], int i, int size, lli dp[])
{
  if (i >= size) return(1);
  if (s[i] == '0') return(0);
  if (dp[i] == -1)
  {
    lli diff = solve(s, i + 1, size, dp);
    if (s[i] <= '2' && i + 1 < size && (s[i] == '1' || s[i + 1] <= '6'))
      diff += solve(s, i + 2, size, dp);
    dp[i] = diff;
  }
  return(dp[i]);
}

lli solveBot(char s[], int size, lli dp[])
{
  dp[size] = 1;
  for (int i = size - 1; i >= 0; i --)
  {
    dp[i] = 0;
    dp[i] += dp[i + 1];
    if (s[i] <= '2' && i + 1 < size && (s[i] == '1' || s[i + 1] <= '6'))
      dp[i] += dp[i + 2];
    if (s[i] == '0')
      dp[i] = 0;
  }
  return(dp[0]);
}

int main()
{
  char s[5001];
  while (scanf("%s", s) && !(s[0] == '0' && s[1] == '\0'))
  {
    getchar(); int size = strlen(s);
    lli dp[size]; //memset(dp, -1, sizeof(dp));
    lli diff = solveBot(s, size, dp); //solve(s, 0, size, dp);
    printf("%lld\n", diff);
    s[1] = '\0';
  }
  return(0);
}