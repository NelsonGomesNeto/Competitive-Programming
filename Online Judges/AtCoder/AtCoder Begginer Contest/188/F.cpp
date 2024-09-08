#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli x, y;

lli eval(lli delta)
{
  lli nx = x + delta;
  lli mult = 0;
  lli total = abs(delta);

  while (2LL * nx > x && 2LL * nx <= y)
    nx *= 2LL, mult++;
  total += mult;
  total += abs(nx - y);

  lli ans = total;
  total -= mult, total -= abs(nx - y);

  nx = x + delta, mult = 0;
  while (2LL * nx > x && nx < y)
    nx *= 2LL, mult++;
  total += mult;
  total += abs(nx - y);

  ans = min(ans, total);

  DEBUG printf("\t%lld - %lld\n", delta, ans);
  return ans;
}
lli ternarySearch(lli lo, lli hi)
{
  while (hi - lo > 10000)
  {
    lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    lli elo = eval(midlo), ehi = eval(midhi);
    if (elo < ehi) hi = midhi + 1;
    else if (ehi < elo) lo = midlo - 1;
    else lo = midlo - 1, ehi = midhi + 1;
  }
  lli ans = eval(lo);
  while (lo <= hi)
    ans = min(ans, eval(lo++));
  return ans;
}

int main()
{
  while (~scanf("%lld %lld", &x, &y))
  {
    lli ans = min({abs(y - x), ternarySearch(0, 1e18), ternarySearch(-1e18, 0), ternarySearch(-1e18, 1e18)});
    for (int i = 0; i <= 1e4; i++)
      ans = min({ans, ternarySearch(-1e7*(i + 1), -1e7*i), ternarySearch(1e7*i, 1e7*(i + 1))});
    // lli ans = ternarySearch(0, 10);
    printf("%lld\n", ans);
  }
  return 0;
}