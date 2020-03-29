#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Notice that we can always make a valid state with min(n - 1, k) empty positions
  Why?
    0 empty positions (k >= 2 and n >= 3 are important):
      if k is even:
        move a person back and forth (i -> j -> ... -> j -> i)
      if k is odd:
        move a person back and forth,
        until there are 3 movements left, (i -> j -> ... -> i -> j -> k -> i)
    1 empty positions:
      use (0 empty positions) until there are only 1 movement
      then move any person anywhere
    m empty positions:
      use (0 emtpy positions) until there are only m movements
      then move m people anywhere

  ans = 0
  for m in [0, min(n - 1, k)]:
    ans += f(m)
  Where f(m) is the number of ways to make a valid state with m empty positions
  That can be decomposed into:
    (the number of ways to place those m empty positions)
      = choose(n, m)
    times
    (the number of ways to populate (n - m) non-empty positions with m people)
      = m stars and n - m - 1 bars
      = StarsAndBars(m, n - m - 1) = choose(m + (n - m - 1), n - m - 1) = choose(n - 1, n - m - 1)
  So, f(m) = choose(n, m) * choose(n - 1, n - m - 1)
*/

const int maxN = 2e5; int n; lli k;
const lli mod = 1e9 + 7;

lli fat[maxN + 2], invFat[maxN + 2];
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
  for (lli i = 1; i <= maxN; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i <= maxN; i++)
    invFat[i] = inv(fat[i]);

  while (scanf("%d %lld", &n, &k) != EOF)
  {
    lli ans = 0;
    for (int m = 0, end = min((lli)n - 1, k); m <= end; m++)
      ans = (ans + choose(n, m) * starsAndBars(m, n - m - 1) % mod) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}