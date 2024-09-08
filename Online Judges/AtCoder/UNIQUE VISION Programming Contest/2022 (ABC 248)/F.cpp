#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 1e5 + 1;
lli mod = 1e9 + 7; // could be two as well

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

const int maxN = 3e3; int n; lli p;
int edges;

lli memo[maxN][maxN][2];
lli solve(int toRemove, int i = 0, bool open = true)
{
  if (toRemove == 0) return 1;
  if (i == n - 1) return toRemove == 1 && !open;
  lli &ans = memo[toRemove][i][open];
  if (ans != -1) return ans;

  // open nothing
  ans = solve(toRemove, i + 1, false);
  // open border
  if (i > 0) ans = (ans + solve(toRemove - 1, i + 1, open)) % p;
  else ans = (ans + solve(toRemove - 1, i + 1, true)) % p;
  // open top
  ans = (ans + solve(toRemove - 1, i + 1, true)) % p;
  // open bottom
  ans = (ans + solve(toRemove - 1, i + 1, true)) % p;

  if (!open && toRemove > 1)
  {
    // open border and top
    ans = (ans + solve(toRemove - 2, i + 1, true)) % p;
    // open border and bottom
    ans = (ans + solve(toRemove - 2, i + 1, true)) % p;
  }

  return ans;
}

int main()
{
  int tests = 0;
  while (~scanf("%d %lld", &n, &p))
  {
    if (tests++) printf("---------------\n");

    mod = p;
    fat[0] = 1;
    for (lli i = 1; i < maxX; i++)
      fat[i] = i * fat[i - 1] % mod;
    for (int i = 0; i < maxX; i++)
      invFat[i] = inv(fat[i]);

    memset(memo, -1, sizeof(memo));
    for (int i = 1; i < n; ++i)
    {
      lli ans = solve(i);
      printf("%lld%c", ans, i + 1 < n ? ' ' : '\n');
    }
  }
  return 0;
}