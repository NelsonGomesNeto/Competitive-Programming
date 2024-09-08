#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 1e6 + 1;
const lli mod = 1e9 + 7;

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

const int maxN = 5e5; int n;

lli brute(vector<int> &piles)
{
  if (piles.size() == n) return 1;

  lli ans = 0;
  for (int i = 0; i < piles.size(); i++)
  {
    int pile = piles[i];
    if (pile >= 2)
    {
      for (int rem = 1; rem < pile; rem++)
      {
        piles[i] -= rem;
        piles.push_back(rem);
        ans = (ans + brute(piles) * choose(pile, rem) * inv(2) % mod) % mod;
        piles[i] += rem;
        piles.pop_back();
      }
    }
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

  // brute
  DEBUG {
    for (n = 1; n <= 20; n++)
    {
      vector<int> piles;
      piles.push_back(n);
      lli ans = brute(piles);
      printf("%d - %lld\n", n, ans);
    }
  }

  while (~scanf("%d", &n))
  {
    lli ans = fat[n] * fat[n - 1] % mod * inv(modPow(2, n - 1)) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}