#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, k;
const lli mod = 1e9 + 7;
lli maximum;
int a[maxN];
int cnt[maxN + 1];

const int maxX = 1e6 + 1;
lli fat[maxX], invFat[maxX];
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
// nn = stars, kk = bars
lli starsAndBars(lli nn, lli kk)
{
  return choose(nn + kk, kk);
}

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxX; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxX; i++)
    invFat[i] = inv(fat[i]);
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    for (int i = 0; i <= n; i++)
      cnt[i] = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      cnt[a[i]]++;
    }
    sort(a, a+n, greater<int>());

    maximum = 0;
    int last = 0;
    for (int i = 0; i < k; i++)
    {
      maximum += a[i];
      last = a[i];
    }

    int fromLast = 0, i = k - 1;
    while (i >= 0 && a[i] == last)
      fromLast++, i--;

    lli ans = choose(cnt[last], fromLast);
    printf("%lld\n", ans);
  }
  return 0;
}
