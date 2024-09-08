#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 1e9 + 7;
lli n, p;

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
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
  while (~scanf("%lld %lld", &n, &p))
  {
    lli ans = (p - 1) * modPow(p - 2, n - 1) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}