#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
lli mod = (lli) 1e9 + 7;
lli dp[(int) 1e7 + 1];

lli run(int now, int n)
{
  if (n == 0) return(!now);

  lli ans = 0;
  for (int i = 0; i < 4; i ++)
    if (i != now)
      ans = (ans + run(i, n - 1)) % mod;

  return(ans);
}

void fillDP()
{
  dp[1] = 0; dp[2] = 3;
  for (int i = 3; i <= 1e7; i ++)
    dp[i] = ((dp[i - 2] * 3) + (dp[i - 1] * 2)) % mod;
}

int main()
{
  fillDP();
  int n; scanf("%d", &n);

  //lli ans = run(0, n);

  printf("%lld\n", dp[n]);

  DEBUG for (int i = 1; i < 10; i ++) printf("%d -> %lld\n", i, run(0, i));

  return(0);
}