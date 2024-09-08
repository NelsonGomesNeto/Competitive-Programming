#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli apSum(lli a1, lli n, lli d)
{
  lli an = a1 + (n - 1)*d;
  return n * (a1 + an) >> 1LL;
}

const int maxN = 100; int n;
lli k[maxN], h[maxN];

int main()
{
  int t;
  while (~scanf("%d", &t))
  {
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d", &n);
      for (int i = 0; i < n; i++) scanf("%lld", &k[i]);
      for (int i = 0; i < n; i++) scanf("%lld", &h[i]);

      lli ans = 0;
      lli prevDamage = 0, lastCastTime = k[n - 1];
      for (int i = n - 1; i >= 0; i--)
      {
        lli currDamage = prevDamage - (lastCastTime - k[i]);
        DEBUG printf("\t%lld %lld %lld - %lld %lld\n", prevDamage, lastCastTime, currDamage, k[i], h[i]);
        if (currDamage < h[i])
        {
          lli manaFromScratch = apSum(1, h[i], 1), manaToAdd = apSum(1, prevDamage + (h[i] - currDamage), 1) - apSum(1, prevDamage, 1);
          DEBUG printf("\t\t%lld %lld\n", manaFromScratch, manaToAdd);
          if (manaFromScratch <= manaToAdd && currDamage <= 0)
          {
            ans += manaFromScratch;
            prevDamage = h[i], lastCastTime = k[i];
          }
          else
          {
            ans += manaToAdd;
            prevDamage = prevDamage + (h[i] - currDamage);
          }
        }
        else
        {
          continue;
        }
      }
      DEBUG printf("%d - %lld\n", tt, ans);
      else printf("%lld\n", ans);
    }
    break;
  }
  return 0;
}
