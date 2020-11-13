#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 400; int n;
const lli inf = 1e18;
lli a[maxN];
lli acc[maxN + 1];
lli lel[maxN + 1];

lli memo[maxN][maxN];
lli pmemo[maxN][maxN];
lli solve(int lo, int hi);
lli pref(int lo, int hi, int x)
{
  if (x == hi) return inf;
  lli &ans = pmemo[lo][hi];
  if (ans != -1) return ans;
  return ans = min(pref(lo, hi, x + 1), solve(lo, x) + solve(x + 1, hi));
}
lli solve(int lo = 0, int hi = n - 1)
{
  if (lo == hi) return 0;
  lli &ans = memo[lo][hi];
  if (ans != -1) return ans;

  ans = inf;
  // for (int x = lo; x < hi; x++)
  ans = min(ans, pref(lo, hi, lo));
  ans += acc[hi + 1] - acc[lo];
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < n; i++)
      acc[i + 1] = acc[i] + a[i];

    memset(memo, -1, sizeof(memo));
    memset(pmemo, -1, sizeof(pmemo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}