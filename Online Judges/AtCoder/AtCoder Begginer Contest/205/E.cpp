#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 2e6 + 1;
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

const int maxN = 1e6;
lli n, m, k;
unordered_map<lli, lli> memo[maxN + 1];
lli solve(lli w = 0, lli b = 0)
{
  if (w > n || b > m) return 0;
  if (w - b > k) return 1;
  if (w == n && b == m) return 0;
  if (memo[w].count(b)) return memo[w][b];
  return memo[w][b] = (solve(w + 1, b) + solve(w, b + 1)) % mod;
}
lli solve2()
{
  lli ans = 0;
  for (int i = 1; i <= n; i++)
  {
    // w - b > k
    int lo = 0, hi = i;
    while (lo < hi)
    {
      int mid = (lo + hi) >> 1;
      if (mid - (i - mid) > k) hi = mid;
      else lo = mid + 1;
    }

    if (lo - (i - lo) > k)
      for (int j = lo; j <= i; j++)
        ans = (ans + starsAndBars(j, i - j)) % mod;
  }
  return ans;
}

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxX; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxX; i++)
    invFat[i] = inv(fat[i]);

  int tt = 0;
  while (~scanf("%lld %lld %lld", &n, &m, &k))
  {
    if (tt++)
    {
      for (int i = 0; i <= maxN; i++) memo[i].clear();
    }

    lli ans = starsAndBars(n, m);
    lli sub = solve();
    lli sub2 = 0; //solve2();

    ans = (ans - sub + mod) % mod;
    printf("%lld\n", ans); fflush(stdout);
  }
  return 0;
}