#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli k;
lli a[maxN], b[maxN];

bool can(lli t)
{
  lli totalViews = 0;
  for (int i = 0; i < n; i++)
    if (a[i] <= t)
    {
      totalViews += (t - a[i]) / b[i] + 1;
      if (totalViews >= k)
        return true;
    }
  DEBUG printf("\t%lld - %lld\n", t, totalViews);
  return false;
}

int main()
{
  while (~scanf("%d %lld", &n, &k))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld %lld", &a[i], &b[i]);

    lli lo = 0, hi = 2e18;
    while (lo < hi)
    {
      lli mid = (lo + hi) >> 1;
      if (can(mid)) hi = mid;
      else lo = mid + 1;
    }
    printf("%lld\n", lo);
  }
  return 0;
}