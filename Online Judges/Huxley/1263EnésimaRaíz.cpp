#include <bits/stdc++.h>
#define lli long long int
#define ldouble long double
using namespace std;

const ldouble EPS = 1e-7;

ldouble power(ldouble x, lli y)
{
  // if (!y) return 1;
  // ldouble ret = power(x, y >> 1LL);
  // ret *= ret; if (y & 1LL) ret *= x;
  // return ret;
  ldouble ans = 1;
  while (y)
  {
    if (y & 1LL) ans *= x;
    x *= x, y >>= 1LL;
  }
  return ans;
}
ldouble root(ldouble x, lli y)
{
  ldouble lo = 0, hi = max((ldouble) 1, x);
  while (lo < hi - EPS)
  {
    ldouble midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    ldouble elo = abs(power(midlo, y) - x), ehi = abs(power(midhi, y) - x);
    if (elo < ehi) hi = midhi;
    else lo = midlo;
  }
  return lo;
}

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    ldouble a; lli n; scanf("%Lf %lld", &a, &n);
    printf("%.1Lf\n", root(a, n));
  }
  return(0);
}