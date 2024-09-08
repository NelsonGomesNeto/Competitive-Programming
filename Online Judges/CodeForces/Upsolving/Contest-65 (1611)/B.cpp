#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli a, b;
lli eval(lli p)
{
  lli aa = a - 2*p, bb = b - 2*p;
  return p + min(aa / 3, bb);
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%lld %lld", &a, &b);
    if (a < b) swap(a, b);

    lli lo = 0, hi = b;
    while (hi - lo > 5)
    {
      lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
      lli elo = eval(midlo), ehi = eval(midhi);
      if (elo > ehi) hi = midhi;
      else lo = midlo;
    }
    lli ans = 0;
    for (lli i = lo; i <= hi; i++)
      ans = max(ans, eval(i));

    printf("%lld\n", ans);
  }
  return 0;
}
