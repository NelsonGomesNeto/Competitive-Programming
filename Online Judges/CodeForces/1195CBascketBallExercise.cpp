#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
lli h[2][maxN];
lli memo[3][maxN];

lli solve(int prv = -1, int j = 0)
{
  if (j == n) return(0);
  if (memo[prv + 1][j] == -1)
  {
    lli ans = solve(prv, j + 1);
    for (int i = 0; i < 2; i ++)
      if (i != prv)
        ans = max(ans, solve(i, j + 1) + h[i][j]);
    memo[prv + 1][j] = ans;
  }
  return(memo[prv + 1][j]);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < 2; i ++)
      for (int j = 0; j < n; j ++)
        scanf("%lld", &h[i][j]);
    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return(0);
}