#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3500; int n, m, k;
lli a[maxN];

lli memo[2][maxN][maxN];
lli solve2(int l = 0, int r = n - 1, int mm = m)
{
  if (mm == 1) return max(a[l], a[r]);
  if (memo[1][l][r] != -1) return memo[1][l][r];
  lli ans = min(solve2(l + 1, r, mm - 1), solve2(l, r - 1, mm - 1));
  return memo[1][l][r] = ans;
}
lli solve(int l = 0, int r = n - 1, int mm = m, int kk = k)
{
  if (mm == 1) return max(a[l], a[r]);
  if (memo[0][l][kk] != -1) return memo[0][l][kk];

  lli ans;
  if (kk)
    ans = max(solve(l + 1, r, mm - 1, kk - 1), solve(l, r - 1, mm - 1, kk - 1));
  else
    ans = solve2(l, r, mm);
  return memo[0][l][kk] = ans;
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        memo[0][i][j] = memo[1][i][j] = -1;
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
