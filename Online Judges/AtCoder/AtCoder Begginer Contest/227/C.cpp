#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli n;
  while (~scanf("%lld", &n))
  {
    lli ans = 0;
    for (lli a = 1; a*a*a <= n; a++)
      for (lli b = a; a*b*b <= n; b++)
      {
        lli cs = n / (a * b) - b + 1;
        ans += cs;
        // lli lo = b, hi = n / (a * b);
        // while (lo < hi)
        // {
        //   lli mid = (lo + hi + 1) >> 1;
        //   if (a * b * mid <= n) lo = mid;
        //   else hi = mid - 1;
        // }
        // assert(a*b*lo <= n);
        // ans += lo;
      }
    printf("%lld\n", ans);
  }
  return 0;
}