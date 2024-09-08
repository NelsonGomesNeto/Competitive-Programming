#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;
lli n, m, L, R;

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
  while (scanf("%lld %lld %lld %lld", &n, &m, &L, &R) != EOF)
  {
    if (n > m) swap(n, m);
    if (n == 1 && !(m & 1) && L < R)
    {
      lli k = R - L + 1;
      lli even = k >> 1LL, odd = (k + 1) >> 1LL;
      lli ans = 0;
      for (lli i = 0, end = m >> 1LL; i <= end; i++)
        ans = (ans + modPow(even, 2LL*i) * modPow(odd, m - 2LL*i) % mod) % mod;
      printf("%lld\n", ans);
    }
    else printf("%lld\n", modPow(R - L + 1, n * m));
  }

  return 0;
}
