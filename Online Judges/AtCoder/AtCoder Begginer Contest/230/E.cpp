#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli n;

int main()
{
  while (~scanf("%lld", &n))
  {
    lli ans = 0;
    for (lli i = 1; i <= n;)
    {
      lli ni = n / i;
      lli lo = i, hi = n;
      while (lo < hi)
      {
        lli mid = (lo + hi + 1) >> 1;
        if (n / mid == ni) lo = mid;
        else hi = mid - 1;
      }
      DEBUG printf("\t%lld %lld\n", lo, hi);
      ans += (lo - i + 1) * ni;

      i = lo + 1;
    }
    printf("%lld\n", ans);
  }
  return 0;
}