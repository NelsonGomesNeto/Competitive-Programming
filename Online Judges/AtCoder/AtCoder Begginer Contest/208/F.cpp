#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 1e9 + 7;
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
const int maxM = 30, maxK = 3e6;
lli n; int m, k;

lli memo[maxM + 1][maxM + 1];
lli f(int nn = n, int mm = m)
{
  if (nn == 0) return 0;
  if (mm == 0) return modPow(nn, k);
  lli &ans = memo[nn][mm];
  if (ans != -1) return ans;
  return ans = f(nn - 1, mm) + f(nn, mm - 1);
}

lli fat[maxK + 1], b[maxK + 1];

int main()
{
  fat[0] = 1;
  for (int i = 1; i <= maxK; i++)
    fat[i] = fat[i - 1] * i % mod;
  b[0] = 1;
  for (int i = 1; i <= maxK; i++)
    b[i] = (1 - b[i - 1] + mod) % mod;

  while (~scanf("%lld %d %d", &n, &m, &k))
  {
    n %= mod;

    lli ans;
    if (n <= 30)
    {
      memset(memo, -1, sizeof(memo));
      ans = f();
    }
    else
    {
      ans = modPow(n, k + 1) * inv(k + 1) % mod;
      ans = (ans + modPow(n, k) * inv(2)) % mod;
      for (int i = 2; i <= k; i++)
        ans = (ans + (b[i] * inv(fat[i]) % mod) % mod
                     * (fat[k] * inv(fat[k - i + 1]) % mod) % mod
                     * modPow(n, k - i + 1) % mod) % mod;

      // ans = ans * n % mod;
    }
    printf("%lld\n", ans);
  }
  return 0;
}