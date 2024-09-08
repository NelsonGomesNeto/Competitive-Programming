#include <stdio.h>
#include <string.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e6 + 1; int n;
const lli mod = 1e9 + 7;

lli fat[maxN], invFat[maxN];
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
lli choose(lli nn, lli kk)
{
  if (nn < kk) return 0;
  if (nn < mod) return fat[nn] * invFat[kk] % mod * invFat[nn - kk] % mod;
  lli ans = 1;
  while (nn || kk)
  {
    lli nnn = nn % mod, kkk = kk % mod;
    nn /= mod, kk /= mod;
    ans = ans * choose(nnn, kkk) % mod;
  }
  return ans;
}
lli starsAndBars(lli nn, lli kk)
{
  return choose(nn + kk, kk);
}

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxN; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxN; i++)
    invFat[i] = inv(fat[i]);

  while (scanf("%d", &n) != EOF)
  {
    lli ans = 0;
    for (int i = 1; i <= n - 1; i++)
      ans = (ans + fatmodPow(10, n - i - 1) % mod) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}