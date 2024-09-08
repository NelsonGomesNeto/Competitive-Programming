#include <bits/stdc++.h>
#define lli long long int
#define DEBUG if(0)
using namespace std;

lli dp[2001][2001], mod = (lli) 1e9 + 7;
set<int> divisors[2001];

void fillDivisors()
{
  for (int i = 1; i < 2001; i ++)
  {
    double root = sqrt(i); int j;
    for (j = 1; j <= root; j ++)
      if (!(i % j))
      {
        divisors[i].insert(j);
        divisors[i].insert(i / j);
      }
    divisors[i].insert(i);
  }
}

lli solve(int n, int i, int k, int prev)
{
  if (i == k) return(1);

  if (dp[i][prev] == -1)
  {
    lli ans = 0;
    for (int j: divisors[prev])
      ans = (ans + solve(n, i + 1, k, j)) % mod;

    dp[i][prev] = ans;
  }

  return(dp[i][prev]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  fillDivisors();
  int n, k; scanf("%d %d", &n, &k);

  lli ans = 0;
  for (int i = 1; i <= n; i ++)
    ans = (ans + solve(n, 1, k, i)) % mod;

  DEBUG {
    for (int i = 1; i <= n; i ++)
    {
      printf("%d -> ", i);
      for (int j: divisors[i])
        printf("%d ", j);
      printf("\n");
    }
  }

  printf("%lld\n", ans);

  return(0);
}