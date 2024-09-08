#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 1e6 + 1;
const lli mod = 1e9 + 7; // could be two as well

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
  // n! / ((n - 2)! * 2!)
  // n * (n - 1) / 2
  return nn * (nn - 1) / 2;

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


const int maxN = 2e5; int n, m, k;
int a[maxN];

int binarySearch(int target, int lo = 0, int hi = n - 1)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (a[mid] <= target) lo = mid;
    else hi = mid - 1;
  }
  return lo;
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
    // scanf("%d %d %d", &n, &m, &k);
    scanf("%d", &n);
    m = 3, k = 2;

    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    sort(a, a+n);

    lli ans = 0;
    for (int i = 0; i + m - 1 < n; i++)
    {
      int p = binarySearch(a[i] + k);
      if (p - i + 1 >= m)
        ans = (ans + choose(p - i, m - 1));
    }
    printf("%lld\n", ans);
  }
  return 0;
}
