#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3; int n;
const lli inf = 1e18;
lli a[maxN];

lli memo[maxN][maxN];
lli solve(bool first = true, int lo = 0, int hi = n - 1)
{
  if (lo == hi) return first ? a[lo] : -a[lo];
  lli &ans = memo[lo][hi];
  if (ans != inf) return ans;

  if (first)
    ans = max(solve(!first, lo + 1, hi) + a[lo], solve(!first, lo, hi - 1) + a[hi]);
  else
    ans = min(solve(!first, lo + 1, hi) - a[lo], solve(!first, lo, hi - 1) - a[hi]);

  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        memo[i][j] = inf;
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}