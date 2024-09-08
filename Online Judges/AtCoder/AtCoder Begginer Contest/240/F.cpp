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

const int maxN = 2e5; int n; lli m;
lli x[maxN], y[maxN];

int main()
{
  int t;
  scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &m);
    for (int i = 0; i < n; i++)
      scanf("%lld %lld", &x[i], &y[i]);

    lli best = LONG_LONG_MIN;
    lli sum = 0, sum2 = 0;
    for (int i = 0; i < n; i++)
    {
      // if (sum >= 0 && sum + x[i] * y[i] <= 0)
      {
        int lo = 1, hi = y[i];
        while (lo < hi)
        {
          int mid = (lo + hi + 1) >> 1;
          if (sum + x[i] * mid >= 0) lo = mid;
          else hi = mid - 1;
        }
        lli peak = sum2 + apSum(sum + x[i], lo, x[i]);
        DEBUG printf("\t%lld\n", peak);
        best = max(best, peak);
      }
      sum2 += apSum(sum + x[i], y[i], x[i]);
      sum += x[i] * y[i];
      DEBUG printf("\t%d %lld %lld\n", i, sum, sum2);
      best = max(best, sum2);
    }
    printf("%lld\n", best);
  }
  return 0;
}