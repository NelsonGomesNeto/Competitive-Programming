#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;
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

const int maxN = 2e5; int n;
lli a[maxN];

lli memo[10][10];
lli solve(int big, int nxt, int rest)
{
  if (!big) return fat[rest + nxt];
  if (!nxt) return 0;
  if (rest == 0) return fat[nxt] * nxt;
  // lli &ans = memo[big][rest];
  // if (ans != -1) return ans;

  lli ans = 0;
  ans = (ans + solve(big - 1, nxt, rest)) % mod;
  ans = (ans + solve(big, nxt - 1, rest) * nxt % mod) % mod;
  ans = (ans + solve(big, nxt, rest - 1) * rest % mod) % mod;

  return ans;
}

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxX; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxX; i++)
    invFat[i] = inv(fat[i]);
  fat[0] = 1;
  for (int i = 1; i <= maxN; i++)
    fat[i] = fat[i - 1] * i % mod;

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    sort(a, a+n);

    if (a[n - 2] == a[n - 1])
      printf("%lld\n", fat[n]);
    else if (a[n - 1] - a[n - 2] > 1)
      printf("0\n");
    else
    {
      int j = n - 2;
      while (j - 1 >= 0 && a[j - 1] == a[j]) j--;
      int cnt = n - 2 - j + 1;

      // memset(memo, -1, sizeof(memo));
      // lli ans = solve(1, cnt, n - (cnt + 1));
      lli ans;
      lli ans2 = fat[n];
      for (int i = cnt; i < n; i++)
      {
        int l = i, r = n - i - 1;
        DEBUG printf("\t%d - %d %d\n", i, l, r);
        ans2 = (ans2 - fat[l] * fat[r] % mod * choose(n - cnt - 1, l - cnt) % mod + mod) % mod;
      }
      DEBUG printf("%lld %lld\n", ans, ans2);
      printf("%lld\n", ans2);
    }
  }
  return 0;
}
