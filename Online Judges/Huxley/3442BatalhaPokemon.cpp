#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = LONG_LONG_MAX;
lli v1, v2, d1, d2, maxTurns;
// (v1, d1) is clodes (starts)
// (v2, d2) is bezaliel

const double eps = 1e-2;
double eval(double turns)
{
  double newD1 = d1 + turns * 50;
  return turns + v2 / newD1;
}
bool ternarySearch()
{
  double lo = 0, hi = maxTurns;
  while (abs(hi - lo) > eps)
  {
    double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    double elo = eval(midlo), ehi = eval(midhi);
    if (elo < ehi) hi = midhi;
    else if (ehi < elo) lo = midlo;
    else lo = midlo, hi = midhi;
  }
  lo = floor(lo), hi = ceil(hi);
  DEBUG printf("\t%lf %lf | %lf %lf\n", lo, hi, eval(lo), eval(hi));
  bool can = false;
  while (lo <= hi)
    can |= ceil(eval(lo++)) <= maxTurns;
  return can;
}

int main()
{
  int n; scanf("%d", &n);
  while (n--)
  {
    scanf("%lld %lld %lld %lld", &v1, &v2, &d1, &d2);
    maxTurns = v1 / d2 + (v1 % d2 != 0);
    DEBUG {
      printf("\tmaxTurns: %lld\n", maxTurns);
      for (int i = 0; i <= maxTurns; i++)
        printf("%4d - %4.3lf\n", i, eval(i));
    }
    printf("%s\n", ternarySearch() ? "Clodes" : "Bezaliel");
  }
  return 0;
}