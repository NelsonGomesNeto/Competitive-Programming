#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, k;
const lli mod = 1e9 + 7;
lli a[maxN];

lli fat[maxN + 1];
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
lli choose(lli nn, lli kk)
{
  return fat[nn] * inv(fat[kk]) % mod * inv(fat[nn - kk]) % mod;
}

int main()
{
  fat[0] = fat[1] = 1;
  for (lli i = 2; i <= maxN; i ++)
    fat[i] = (i * fat[i - 1]) % mod;

  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);
    sort(a, a+n);

    if (k == 1)
    {
      printf("0\n");
      continue;
    }

    lli maximum = 0, minimum = 0;
    for (int i = 0; i < n - k + 1; i ++)
      minimum = (minimum + a[i] * choose(n - i - 1, k - 1) % mod) % mod;
    for (int i = k - 1; i < n; i ++)
      maximum = (maximum + a[i] * choose(i, k - 1) % mod) % mod;

    lli ans = (maximum - minimum + mod) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}