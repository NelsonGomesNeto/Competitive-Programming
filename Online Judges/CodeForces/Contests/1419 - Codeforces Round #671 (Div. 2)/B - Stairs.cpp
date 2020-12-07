#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli apSum(lli a1, lli an, lli n)
{
  return(n * (a1 + an) / 2.0);
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
  {
    for (int tt = 1; tt <= t; tt++)
    {
      lli x; scanf("%lld", &x);
      lli ans = 0;
      for (int i = 1; i <= 60; i++)
      {
        lli size = (1LL << i) - 1;
        lli cost = apSum(1, size, size);
        DEBUG printf("\t%d - %lld %lld %lld\n", i, x, size, cost);
        if (cost <= x)
          x -= cost, ans = i;
        else
          break;
      }
      printf("%lld\n", ans);
    }
  }
  return 0;
}
