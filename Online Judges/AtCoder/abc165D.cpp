#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli a, b, n;

lli evaluate(lli x)
{
  x = min(n, x / b * b + b - 1);
  return (a*x)/b - a*(x/b);
}
lli ternarySearch(lli lo = 0, lli hi = n)
{
  while (lo < hi - 3)
  {
    lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    lli elo = evaluate(midlo), ehi = evaluate(midhi);
    if (elo > ehi) hi = midhi;
    else if (ehi > elo) lo = midlo;
    else lo = midlo, hi = midhi;
  }
  lli ans = evaluate(lo++);
  while (lo <= hi) ans = max(ans, evaluate(lo++));
  return ans;
}

int main()
{
  while (scanf("%lld %lld %lld", &a, &b, &n) != EOF)
    printf("%lld\n", ternarySearch());
  return 0;
}