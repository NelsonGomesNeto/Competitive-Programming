#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5 + 1;
const lli mod = 1e9 + 7;
lli n, a, b;

lli fat[maxN];
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
lli choose(lli nn, lli k)
{
  lli res = 1;
  for (lli i = nn; i > nn - k; i --)
    res = (res * i) % mod;
  return res * inv(fat[k]) % mod;
}

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxN; i ++)
    fat[i] = fat[i - 1] * i % mod;

  while (scanf("%lld %lld %lld", &n, &a, &b) != EOF)
  {
    lli ans = (modPow(2, n) - choose(n, a) - choose(n, b) - 1LL + mod + mod) % mod;
    if (ans < 0)
      while (1);
    printf("%lld\n", ans);
  }
  return 0;
}