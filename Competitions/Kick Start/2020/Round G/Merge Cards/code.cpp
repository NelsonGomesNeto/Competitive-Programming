#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n;
lli a[maxN];
lli acc[maxN + 1];

ldouble memo[maxN + 1][maxN];
ldouble pre[maxN], suf[maxN];
ldouble solve(int lo = 0, int hi = n - 1)
{
  if (lo == hi) return 0;
  ldouble &ans = memo[lo][hi];
  if (ans != -1) return ans;

  ldouble sum = pre[lo] + suf[hi];
  // for (int i = lo; i < hi; i++)
  //   sum += solve(lo, i) + solve(i + 1, hi);
  ans = acc[hi + 1] - acc[lo] + sum / (ldouble)(hi - lo);
  pre[lo] += ans;
  suf[hi] += ans;
  return ans;
}
ldouble solve4()
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      memo[i][j] = 0;
    pre[i] = suf[i] = 0;
  }

  for (int sz = 1; sz <= n; sz++)
    for (int lo = 0; lo + sz < n; lo++)
    {
      int hi = lo + sz;
      memo[lo][hi] += pre[lo];
      memo[lo][hi] += suf[hi];
      // for (int i = lo; i < hi; i++)
      // {
      //   memo[lo][hi] += memo[lo][i];
      //   memo[lo][hi] += memo[i + 1][hi];
      // }
      memo[lo][hi] /= (ldouble)sz;
      memo[lo][hi] += acc[hi + 1] - acc[lo];

      pre[lo] += memo[lo][hi];
      suf[hi] += memo[lo][hi];
    }

  return memo[0][n - 1];
}
ldouble solve2(int sz = n, int i = 0)
{
  if (sz == 1) return 0;
  ldouble &ans = memo[sz][i];
  if (ans != -1) return ans;

  ldouble sum = 0;
  for (int x = 0; x < sz - 1; x++) // cutpoints
    sum += solve2(x + 1, i) + solve2(sz - x - 1, i + x + 1);
  return ans = acc[i + sz] - acc[i] + sum / (ldouble)(sz - 1);
}
ldouble prefix[maxN + 1], suffix[maxN + 1];
ldouble solve3()
{
  for (int i = 0; i <= n; i++)
  {
    for (int j = 0; j < n; j++)
      memo[i][j] = 0;
    prefix[i] = suffix[i] = 0;
  }

  for (int i = 0; i < n; i++) memo[1][i] = 0;

  for (int sz = 2; sz <= n; sz++)
    for (int i = 0; i + sz - 1 < n; i++)
    {
      // sum(memo[k][i], k = [1 : sz - 1])
      // sum(memo[k][i + x + 1], k = [1 : sz - 1])

      memo[sz][i] += prefix[i];
      memo[sz][i] += suffix[i + sz];
      // for (int x = 0; x < sz - 1; x++)
      // {
      //   memo[sz][i] += memo[x + 1][i];
      //   memo[sz][i] += memo[sz - x - 1][i + x + 1];
      //     // sz - x - 1, i + x + 1
      //     // (sz - x - 1) + (i + x + 1) = i + sz (for all x)
      // }
      memo[sz][i] /= (ldouble)(sz - 1);
      memo[sz][i] += acc[i + sz] - acc[i];

      prefix[i] += memo[sz][i];
      suffix[i + sz] += memo[sz][i];
    }

  return memo[n][0];
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < n; i++)
      acc[i + 1] = acc[i] + a[i];

    for (int i = 0; i <= n; i++)
      for (int j = 0; j < n; j++)
        memo[i][j] = -1;
    // ldouble ans = solve();
    memset(pre, 0, sizeof(pre)), memset(suf, 0, sizeof(suf));
    ldouble ans = solve();
    printf("Case #%d: %.15Lf\n", tt, ans);
  }
  return 0;
}