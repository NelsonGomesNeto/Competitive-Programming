#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli n;

double eval(double c2)
{
  double c1 = n - 2*c2;
  return abs(c1 - c2);
}
lli eval2(lli c2)
{
  lli c1 = n - 2*c2;
  return abs(c1 - c2);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld", &n);
    double lo = 0, hi = 1e9;
    while (abs(hi - lo) > 1)
    {
      double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
      if (eval(midlo) < eval(midhi)) hi = midhi;
      else lo = midlo;
    }

    lli c1, c2;
    lli a, b;
    double best = 1e18;
    lo--;
    while (lo <= hi + 2)
    {
      if (eval2(ceil(lo)) < best)
      {
        a = floor(n - 2*ceil(lo));
        b = ceil(lo);
        if (a + 2*b == n)
        {
          best = eval2(ceil(lo));
          c1 = a, c2 = b;
        }
      }
      lo++;
    }
    printf("%lld %lld\n", c1, c2);
  }
  return 0;
}
