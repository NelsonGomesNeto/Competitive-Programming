#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxSize = 1e6 + 1;
char ss[maxSize];
string s; int n, k;

const int maxN = 1e6 + 1;
const lli mod = 1e9 + 7; // could be two as well

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
// nn = stars, kk = bars
lli starsAndBars(lli nn, lli kk)
{
  return choose(nn + kk, kk);
}

lli memo[maxN][2];
lli solve(int i = 0, int j = 0)
{
  if (i > k || j > n) return 0;
  if (i == k && j == n) return 1;
  if (memo[i][j == n] != -1) return memo[i][j == n];
  lli ans = (lli)(25 + (j == n)) * solve(i + 1, j) % mod;
  ans = (ans + solve(i, j + 1)) % mod;
  return memo[i][j == n] = ans;
}

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxN; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxN; i++)
    invFat[i] = inv(fat[i]);

  while (scanf("%d", &k) != EOF)
  {
    scanf(" %s", ss);
    s = string(ss);
    n = s.size();

    /*
      The final string will have msz = n + k letters
      26^msz == choose any letter for each position
      Out of those, the only final strings we can't build are
      the ones in which there's no "s" as a subsequence
    */

    // lli ans = modPow(25, k);
    // ans = ans * (starsAndBars(n, k)) % mod;
    // memset(memo, -1, sizeof(memo));
    lli ans = 0;
    for (int i = 0; i <= k; i++)
    {
      lli hehe = choose(n + k - i, n);
      DEBUG printf("\t%d %d %lld\n", i, n + k - i, hehe);
      ans = (ans + modPow(26, i) * modPow(25, k - i) % mod * hehe % mod) % mod;
    }
    // for (int i = 0, j = k + n; i < n; i++, j--)
    //   ans = ans * j % mod;
    // printf("%d - %lld\n", k, ans);
    // lli ans = solve();
    printf("%lld\n", ans);
    // for (n = 1; n <= n; n++)
    // {
    //   lli ans = solve();
    //   printf("%d - %lld\n", n, ans);
    // }
  }
  return 0;
}