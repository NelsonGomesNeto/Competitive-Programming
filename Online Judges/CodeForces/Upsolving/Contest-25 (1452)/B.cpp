#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN];

// all blocks will have to sum to a value

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    lli total = 0;
    lli maxValue = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      total += a[i];
      maxValue = max(maxValue, a[i]);
    }

    lli d = n - 1;
    lli lo = 0, hi = 1e13;
    while (lo < hi)
    {
      lli mid = (lo + hi) >> 1;
      if ((d * (maxValue + mid)) - total >= 0) hi = mid;
      else lo = mid + 1;
    }
    lli ans = (d * (maxValue + lo)) - total;
    printf("%lld\n", ans);
  }
  return 0;
}
