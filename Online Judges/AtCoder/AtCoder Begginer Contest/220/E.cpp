#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, d;
const lli mod = 998244353;

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}

int main()
{
  while (~scanf("%d %d", &n, &d))
  {
    lli single = 0, multiple = 0;

    lli fit = n - d;
    if (fit >= 1)
    {
      lli roots = (modPow(2, fit) - 1 + mod) % mod;
      single = roots * modPow(2, d) % mod * 2 % mod;
    }

    for (lli leftD = 1; leftD < d; leftD++)
    {
      lli biggestSide = max(leftD, d - leftD);
      lli fit = n - biggestSide;
      if (fit >= 0)
      {
        lli roots = (modPow(2, fit) - 1 + mod) % mod;
        multiple = (multiple + roots
                              * modPow(2, leftD - 1) % mod % mod
                              * modPow(2, d - leftD - 1) % mod % mod
                              * 2 % mod) % mod;
      }
    }

    DEBUG printf("\t%lld %lld\n", single, multiple);
    lli ans = (single + multiple) % mod;

    printf("%lld\n", ans);
  }
  return 0;
}