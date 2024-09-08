#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli x, y, a, b;

double eval(double n)
{
  if (x - a*n < 0 || y - b*n < 0) return 0;
  double m = min((x - a*n) / b, (y - b*n) / a);
  return n + m;
}
lli evalFloor(double n)
{
  lli nn = floor(n);
  if (x - a*nn < 0 || y - b*nn < 0) return 0;
  lli m = min((x - a*nn) / b, (y - b*nn) / a);
  return n + m;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld %lld %lld %lld", &x, &y, &a, &b);

    double lo = 0, hi = 1e9;
    while (hi - lo >= 10)
    {
      double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
      double elo = eval(midlo), ehi = eval(midhi);
      if (elo >= ehi) hi = midhi;
      else lo = midlo;
    }
    lli ans = 0;
    for (lli i = floor(lo); i <= ceil(hi); i++)
      ans = max(ans, evalFloor(i));
    printf("%lld\n", ans);
  }
  return 0;
}