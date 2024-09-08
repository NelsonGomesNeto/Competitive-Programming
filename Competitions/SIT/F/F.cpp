#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli n, m;
  while (~scanf("%lld %lld", &n, &m))
  {
    lli ans = 0;
    for (int i = 1; i <= n; i++)
    {
      lli lo = 0, hi = n - 1;
      while (lo < hi)
      {
        lli mid = (lo + hi + 1) >> 1;
        if (mid + i*(m - 1) < n) lo = mid;
        else hi = mid - 1;
      }

      if (lo + i*(m - 1) < n)
        ans += lo + 1;
    }
    printf("%lld\n", ans);
  }
  return 0;
}