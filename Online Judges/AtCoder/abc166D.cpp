#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli pot(lli x)
{
  return x*x*x*x*x;
}

lli bs(lli res)
{
  lli lo = 0, hi = 1000;
  while (lo < hi)
  {
    lli mid = (lo + hi) >> 1;
    if (pot(mid) >= res) hi = mid;
    else lo = mid + 1;
  }
  if (pot(lo) == res) return lo;
  lo = -1000, hi = 0;
  while (lo < hi)
  {
    lli mid = (lo + hi + 1) >> 1;
    if (pot(mid) <= res) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main()
{
  lli x;
  while (scanf("%lld", &x) != EOF)
  {
    lli a, b;
    for (a = -1000; ; a++)
    {
      lli res = pot(a) - x;
      b = bs(res);
      DEBUG printf("\t%lld %lld\n", a, b);
      if (pot(b) == res)
        break;
    }
    printf("%lld %lld\n", a, b);
  }
  return 0;
}