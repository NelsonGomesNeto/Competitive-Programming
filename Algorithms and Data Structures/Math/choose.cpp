#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* choose(n, k) = n! / (k! * (n - k)!)
  cases where n is too large, but close to k:
    choose(n, k) = pi(k + 1 to n, i) / (n - k)!
  Pascal's Triangle:
    1      1      1      1      1 
    1      2      3      4      5 
    1      3      6     10
    1      4     10
    1      5
    1
    matrix(r, c) = choose(r + c, c)
    (0-indexed)
*/

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

  return 0;
}