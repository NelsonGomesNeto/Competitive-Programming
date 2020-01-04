#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5 + 1; int n;
const lli mod = 1e9 + 7;
lli a[maxN];
lli r[60][2][maxN];

lli multMod(lli x, lli y)
{
  lli ans = 0;
  while (y)
  {
    if (y & 1LL) ans = (ans + x) % mod;
    x = (x + x) % mod, y >>= 1LL;
  }
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);
    for (lli bit = 0; bit < 60; bit ++)
    {
      r[bit][0][n] = r[bit][1][n] = 0;
      for (int i = n - 1; i >= 0; i --)
      {
        r[bit][0][i] = !((a[i] >> bit) & 1LL) + r[bit][0][i + 1];
        r[bit][1][i] = ((a[i] >> bit) & 1LL) + r[bit][1][i + 1];
      }
    }

    lli ans = 0;
    for (lli bit = 0; bit < 60; bit ++)
      for (int i = 0; i < n - 1; i ++)
        ans = (ans + (1LL << bit) % mod * r[bit][!((a[i] >> bit) & 1LL)][i + 1] % mod) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}