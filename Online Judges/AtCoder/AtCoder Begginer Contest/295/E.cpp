#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 2e3 + 1;
const lli mod = 998244353LL;

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}
lli fat[maxX], invFat[maxX];
lli choose(lli nn, lli kk)
{
  if (nn < kk)
    return 0;
  if (nn < mod)
    return fat[nn] * invFat[kk] % mod * invFat[nn - kk] % mod;
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

const int maxN = 2e3;
int n, m, k;
vector<int> a;
int zeros;
lli xModPow[maxN + 1][maxN + 1];
lli xModRem[maxN + 1][maxN + 1];

lli memo[maxN + 2][maxN + 2];
lli permutations(int x, int y)
{
  if (x < 0 || y < 0) return 0;
  // DEBUG printf("\t\t%d %d %d - %lld\n", x, y, z, memo[x][z]);
  if (x + y == 0) return 1;
  lli& ans = memo[x][y];
  if (ans != -1) return ans;
  ans = (permutations(x - 1, y) + permutations(x, y - 1)) % mod;
  return ans;
}
void permutations2()
{
  memset(memo, 0, sizeof(memo));
  memo[0][0] = 1;
  for (int i = 1; i <= n; ++i)
    memo[i][0] += memo[i - 1][0];
  for (int j = 1; j <= n; ++j)
    memo[0][j] += memo[0][j - 1];
  for (int i = 1; i <= n; ++i)
    for (int j = 1, end = n - i; j <= end; ++j)
    {
      lli& ans = memo[i][j];
      ans = (ans + memo[i - 1][j] + memo[i][j - 1]) % mod;
    }
  for (int i = 0; i <= n; ++i)
    for (int j = 0, end = n - i; j <= end; ++j)
      memo[i][j] = memo[i][j] * starsAndBars(i + j, zeros - (i + j)) % mod;
}
inline lli smallFixMod(lli x) { return x >= mod ? x - mod : x;}

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxX; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxX; i++)
    invFat[i] = inv(fat[i]);

  for (int x = 0; x <= maxN; ++x)
  {
    xModPow[x][0] = 1;
    for (int i = 1; i <= maxN; ++i)
      xModPow[x][i] = xModPow[x][i - 1] * x % mod;
  }

  while (~scanf("%d %d %d", &n, &m, &k))
  {
    const lli invM = inv(m);
    a.clear();
    a.resize(n);
    for (int& aa : a) scanf("%d", &aa);

    zeros = 0;
    for (const int aa : a) zeros += aa == 0;
    const lli invMpZeros = modPow(invM, zeros);
    permutations2();

    lli ans = 0;
    for (int x = 1; x <= m; ++x)
    {
      int lessThenX = 0;
      for (const int aa : a) lessThenX += aa != 0 && aa < x;
      int xCount = 0;
      for (const int aa : a) xCount += aa == x;

      lli p = 0;
      for (int below = lessThenX, addedBelow = 0; below < k && addedBelow <= zeros; ++below, ++addedBelow)
      {
        const int needed = max(xCount, k - below);
        const int delta = max(0, needed - xCount);
        lli p2 = 0;

        for (int addedExact = delta; addedBelow + addedExact <= zeros; ++addedExact)
        {
          const int remaining = zeros - addedBelow - addedExact;
          const lli perm = memo[addedBelow][addedExact];

          // DEBUG {
          //   double pb = pow((double)(x - 1) / m, addedBelow);
          //   double pe = pow((double)1 / m, addedExact);
          //   double pr = pow((double)(m - x) / m, remaining);
          //   double prob2 = perm * pb * pe * pr;
          //   printf("\t\t%d %d | %d %d %d | %lf %lf %lf | %lld %lf\n", below, exact, addedBelow, addedExact, remaining, pb, pe, pr, perm, prob2);
          //   prob += prob2;
          // }

          /*
          ((x - 1) / m)^addedBelow * (1 / m)^addedExact * ((m - x) / m)^remaining
          */
          const lli nowP = xModPow[m - x][remaining];
          p2 = smallFixMod(p2 + perm * nowP % mod);
        }
        p2 = p2 * xModPow[x - 1][addedBelow] % mod;
        p = smallFixMod(p + p2);
      }
      p = p * invMpZeros % mod;

      // lli prob = p(x, zeros, lessThenX, xCount);
      // DEBUG {
      //   target = x;
      //   double prob2 = solve2(zeros, lessThenX, xCount);
      //   printf("\t%d | %d %d | %lf\n", x, lessThenX, xCount, prob2);
      // }
      ans = (ans + x * p % mod) % mod;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
