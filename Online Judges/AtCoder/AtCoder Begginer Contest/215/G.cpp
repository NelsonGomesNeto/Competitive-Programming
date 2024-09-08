#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial
  Let's fix K
  We want to calculate the expected number of different colors after choosing K candies.
  Expected Value = sum of all occurencies values / occurrencies count

  

*/

const int maxX = 1e6 + 1;
const lli mod = 998244353; // could be two as well

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

const int maxN = 5e4; int n;
lli c[maxN];
vector<lli> cs;

lli cnt[maxN];
vector<lli> cnts;
lli cntCnt[maxN + 1];

lli ans[maxN + 1];

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxX; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxX; i++)
    invFat[i] = inv(fat[i]);

  while (~scanf("%d", &n))
  {
    cs.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &c[i]);
      cs.push_back(c[i]);
    }

    sort(cs.begin(), cs.end());
    cs.resize(distance(cs.begin(), unique(cs.begin(), cs.end())));

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
    {
      c[i] = lower_bound(cs.begin(), cs.end(), c[i]) - cs.begin();
      cnt[c[i]]++;
    }

    cnts.clear();
    for (int i = 0; i < cs.size(); i++)
      cnts.push_back(cnt[i]);
    sort(cnts.begin(), cnts.end());
    cnts.resize(distance(cnts.begin(), unique(cnts.begin(), cnts.end())));

    memset(cntCnt, 0, sizeof(cntCnt));
    for (int i = 0; i < cs.size(); i++)
      cntCnt[cnt[i]]++;

    for (int k = 1; k <= n; k++)
    {
      lli sum = 0;
      // for (int i = 0; i < cs.size(); i++)
      // {
      //   lli x = (choose(n, k) - choose(n - cnt[i], k) + mod) % mod;
      //   sum = (sum + x) % mod;
      // }
      for (int i = 0; i < cnts.size(); i++)
      {
        lli x = (choose(n, k) - choose(n - cnts[i], k) + mod) % mod;
        sum = (sum + x * cntCnt[cnts[i]] % mod) % mod;
      }
      ans[k] = sum * inv(choose(n, k)) % mod;
    }

    for (int k = 1; k <= n; k++)
      printf("%lld\n", ans[k]);
  }
  return 0;
}