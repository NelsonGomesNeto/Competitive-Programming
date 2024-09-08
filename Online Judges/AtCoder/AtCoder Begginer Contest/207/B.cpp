#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli a, b, c, d;
  while (~scanf("%lld %lld %lld %lld", &a, &b, &c, &d))
  {
    lli lo = 0, hi = 1e13;
    while (lo < hi)
    {
      lli mid = (lo + hi) >> 1;
      lli cyan = a + b * mid;
      lli red = c * mid;
      if (cyan <= red * d) hi = mid;
      else lo = mid + 1;
    }

    lli cyan = a + b * lo;
    lli red = c * lo;
    if (cyan > red * d) printf("-1\n");
    else printf("%lld\n", lo);
  }
  return 0;
}