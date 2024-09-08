#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*

k^n <- positions

m^(k^n)
m * m * ... * m
^ (k^n) times

mod 998244353

*/

const lli baseMod = 998244353;
lli n, k, m;

lli modPow(lli x, lli y, lli mod)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}

int main()
{
  while (~scanf("%lld %lld %lld", &n, &k, &m))
  {
    lli ans = modPow(m, modPow(k, n, baseMod - 1), baseMod);
    // if (m % baseMod == 0) ans = 0;
    printf("%lld\n", ans);
  }
  return 0;
}