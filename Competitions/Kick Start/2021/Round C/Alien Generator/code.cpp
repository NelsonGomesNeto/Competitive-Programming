#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli apSum(lli a1, lli n, lli d)
{
  lli an = a1 + (n - 1)*d;
  return n * (a1 + an) >> 1LL;
}

lli g;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld", &g);

    lli ans = 0;
    for (int i = 1, end = 2*sqrt(g); i <= end; i++)
    {
      lli lo = 1, hi = 1e12;
      while (lo < hi)
      {
        lli mid = (lo + hi + 1) >> 1;
        if (apSum(mid, i, 1) <= g) lo = mid;
        else hi = mid - 1;
      }
      DEBUG printf("\t%d %lld %lld\n", i, lo, apSum(lo, i, 1));
      ans += apSum(lo, i, 1) == g;
    }

    printf("Case #%d: %lld\n", tt, ans);
  }
 return 0;
}