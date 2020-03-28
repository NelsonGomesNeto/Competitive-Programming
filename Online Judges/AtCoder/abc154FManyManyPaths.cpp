#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  I really recommend you to emulate the matrix, you will see Pascal's Triangle

  I will denote sum(f(i) where i is from 0 to n) as f(0 : n)

  Notice that f(r + 1, c) = f(r, 0 : c)
    Looking at the base case will make you understand it easier:
    f(1, c) = f(0, 0 : c)
      Notice how reaching the last row is a dead end, since there's no more moves
      So by verifying every possible way to reach a position and then go to the
      last row (dead end): we will be accounting for all possible ways to reach
      (r + 1, c)

  A very fast way to get the sum of a submatrix is through accumulated sum
  Suppose you have an O(1) function acc(r, c) that calculates mat(0 : r, 0 : c)
  mat(r1 : r2, c1 : c2) = acc(r2, c2) - acc(r1 - 1, c2) - acc(r2, c1 - 1) + acc(r1 - 1, c1 - 1)

  Back to the original problem, suppose you had g(r, c) = f(0 : r, 0 : c);
  the problem's answer would be g(r2, c2) - g(r1 - 1, c2) - g(r2, c1 - 1) + g(r1 - 1, c1 - 1)

  Let's dig into g: g(r, c) = f(0 : r, 0 : c), remember that f(r + 1, c) = f(r, 0 : c)
  So we could reduce f(0 : r, 0 : c) to f(1 : r + 1, c)
  But f(r, c + 1) = f(0 : r, c) is also true, so we can apply the same logic to reduce
  even further!
  g(r, c) = f(0 : r, 0 : c) = f(1 : r + 1, c) = f(r + 1, c + 1)
  AMAZING

  But how the hell can we calculate f(r, c)? Pascal's Triangle
  f(r, c) = choose(r + c, c)
*/

const int maxN = 2e6 + 3;
lli lol[3000][3000], acc[3000][3000];
const lli mod = 1e9 + 7;
lli r1, r2, c1, c2;

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

lli f(lli r, lli c)
{
  return choose(r + c, c);
}

lli g(lli r, lli c)
{
  // f(0 to r, 0 to c)
  return f(r + 1, c + 1);
}

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxN; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxN; i++)
    invFat[i] = inv(fat[i]);

  while (scanf("%lld %lld %lld %lld", &r1, &c1, &r2, &c2) != EOF)
  {
    DEBUG {
      int nn = 3000;
      for (int i = 0; i < nn; i ++)
        lol[i][0] = lol[0][i] = 1;
      lol[0][0] = 1;

      for (int i = 1; i < nn; i ++)
        for (int j = 1; j < nn; j ++)
          lol[i][j] = (lol[i][j - 1] + lol[i - 1][j]) % mod;
      for (int i = 1; i < nn; i ++)
        for (int j = 1; j < nn; j ++)
          acc[i][j] = (acc[i - 1][j] + acc[i][j - 1] - acc[i - 1][j - 1] + lol[i][j] + mod) % mod;

      int n = 10;
      for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
          printf("%6lld%c", lol[i][j], j < n - 1 ? ' ' : '\n');
      for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
          printf("%6lld%c", acc[i][j], j < n - 1 ? ' ' : '\n');

      lli qq = 0;
      for (int i = r1; i <= r2; i ++)
        for (int j = c1; j <= c2; j ++)
          qq = (qq + lol[i][j]) % mod;

      lli ans = (g(r2, c2) - g(r1 - 1, c2) - g(r2, c1 - 1) + g(r1 - 1, c1 - 1) + mod + mod) % mod;
      printf("%lld %lld\n", ans, qq);
    }
    lli ans = (g(r2, c2) - g(r1 - 1, c2) - g(r2, c1 - 1) + g(r1 - 1, c1 - 1) + mod + mod) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}