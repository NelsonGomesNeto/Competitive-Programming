#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli p[maxN], pi[maxN + 1];
const lli mod = 998244353;

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = (ans * x) % mod;
    x = (x * x) % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &p[i]);
      p[i] = (p[i] * inv(100)) % mod;
    }

    pi[0] = 1;
    for (int i = 0; i < n; i ++)
      pi[i + 1] = (pi[i] * p[i]) % mod;

    DEBUG
      for (int i = 0; i <= n; i ++)
        printf("%lld%c", pi[i], i < n ? ' ' : '\n');

    lli e1 = 0;
    for (int i = 0; i < n; i ++)
      e1 = (e1 + pi[i]) % mod;
    e1 = e1 * inv(pi[n]) % mod;
    printf("%lld\n", e1);
  }
  return 0;
}
