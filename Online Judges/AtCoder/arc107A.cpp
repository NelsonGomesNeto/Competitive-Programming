#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;
lli a, b, c, inv2;

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

lli apSum(lli a1, lli an, lli n)
{
  return(n * (a1 + an) % mod * inv2 % mod);
}

int main()
{
  inv2 = inv(2);
  while (scanf("%lld %lld %lld", &a, &b, &c) != EOF)
  {
    lli ans = apSum(1, a, a) * apSum(1, b, b) % mod * apSum(1, c, c) % mod;
    // for (lli i = 1; i <= a; i++)
    //   for (lli j = 1; j <= b; j++)
    //   {
    //     lli curr = i * j % mod * apSum(1, c, c) % mod;
    //     ans = (ans + curr) % mod;
    //     // for (lli k = 1; k <= c; k++)
    //     // {
    //     //   lli curr = i * j % mod * k % mod;
    //     //   ans = (ans + curr) % mod;
    //     //   printf("%lld %lld %lld = %lld\n", i, j, k, curr); 
    //     // }
    //   }

    printf("%lld\n", ans);
  }
  return 0;
}