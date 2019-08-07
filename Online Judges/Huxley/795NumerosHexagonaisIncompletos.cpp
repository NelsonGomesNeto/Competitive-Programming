#include <bits/stdc++.h>
long long int dp[50001];
long long int six[50001];

int fill()
{
  six[1] = 1; six[2] = 6;
  dp[1] = 1; dp[2] = 6;
  for (int i = 3; i <= 50000; i ++) six[i] = 6 * (i - 1);
  for (int i = 3; i <= 50000; i ++) dp[i] = six[i] + dp[i - 2];
}

int main()
{
  fill();
  int n;
  while (scanf("%d", &n) != EOF)
    printf("%lld\n", dp[n]);

  return(0);
}