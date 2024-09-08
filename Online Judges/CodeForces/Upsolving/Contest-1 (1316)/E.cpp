#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxP = 7; int n, p, k;
const lli inf = 1e16;
lli a[maxN], s[maxN][maxP];

lli memo[maxN][(1 << maxP) - 1][2];
int ones(int num)
{
  int o = 0;
  while (num) num >>= 1, o ++;
  return o;
}
lli solve(int i = 0, int pBitmask = 0, int kk = k)
{
  DEBUG printf("\t%d %d (%d) %d\n", i, pBitmask, ((1 << p) - 1), kk);
  if (n - i < kk) return -inf;
  if (i == n) return pBitmask == ((1 << p) - 1) ? 0 : -inf;
  if (memo[i][pBitmask][kk > ones(pBitmask)] != -1) return memo[i][pBitmask][kk > ones(pBitmask)];

  lli ans = solve(i + 1, pBitmask, kk);
  if (kk) ans = max(ans, solve(i + 1, pBitmask, kk - 1) + a[i]);
  for (int pp = 0; pp < p; pp ++)
    if (!(pBitmask & (1 << pp)))
      ans = max(ans, solve(i + 1, pBitmask | (1 << pp), kk) + s[i][pp]);
  return memo[i][pBitmask][kk > ones(pBitmask)] = ans;
}

int main()
{
  while (scanf("%d %d %d", &n, &p, &k) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < p; j ++)
        scanf("%lld", &s[i][j]);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
