#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 1300031;
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
lli modApSum(lli a1, lli n, lli d)
{
  lli an = (a1 % mod + (n - 1 + mod)*d % mod) % mod;
  return n * (a1 + an) % mod * inv(2) % mod;
}

const int maxN = 20; lli i, f; int n;

lli trucks[maxN];
vector<lli> hehe;
lli calc(lli d, bool print = false)
{
  lli sz = f / d - (i - 1) / d;
  lli start = i <= d ? 1 : i / d;
  lli total = modApSum(d*start, sz, d);
  DEBUG printf("\t%lld %lld %lld - %lld\n", d, sz, start, total);
  return total;
}

int main()
{
  while (~scanf("%lld %lld %d", &i, &f, &n))
  {
    if (i + f + n == 0) break;

    set<lli> has;
    hehe.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &trucks[i]);
      hehe.push_back(trucks[i]);
      has.insert(trucks[i]);
    }
    sort(hehe.begin(), hehe.end());
    hehe.resize(distance(hehe.begin(), unique(hehe.begin(), hehe.end())));

    // lli ans = 0;
    // for (int i = 0; i < hehe.size(); i++)
    // {
    //   if (hehe[i] > f) continue;
    //   ans = (ans + calc(hehe[i], true)) % mod;
    // }

    // DEBUG printf("--------- removing\n");
    // for (int bit = 0, end = 1 << hehe.size(); bit < end; bit++)
    // {
    //   if (__builtin_popcount(bit) <= 1) continue;

    //   lli l = 1;
    //   for (int i = 0; i < hehe.size(); i++)
    //     if (bit & (1 << i))
    //     {
    //       l = lcm(l, hehe[i]);
    //       if (l > f) break;
    //     }
    //   bool toSkip = false;
    //   // for (int i = 0; i < hehe.size(); i++)
    //   //   if (bit & (1 << i))
    //   //     toSkip |= hehe[i] == l;
    //   if (l > f || toSkip) continue;
    //   // removed.insert(curr);
    //   DEBUG printf("\t\t%d - %lld - %lld\n", bit, l, calc(l));
    //   ans = (ans + (__builtin_popcount(bit) & 1 ? 1 : -1)*calc(l, true) % mod + mod) % mod;
    // }

    set<lli> blacklist;
    for (int bit = 0, end = 1 << hehe.size(); bit < end; bit++)
    {
      if (__builtin_popcount(bit) <= 1) continue;

      lli l = 1;
      for (int i = 0; i < hehe.size(); i++)
        if (bit & (1 << i))
        {
          l = lcm(l, hehe[i]);
          if (l > f) break;
        }
      if (l > f) continue;

      if (has.count(l)) blacklist.insert(l);
    }

    vector<int> rem;
    for (int h: hehe) if (!blacklist.count(h)) rem.push_back(h);

    lli ans = 0;
    for (int i = 0; i < rem.size(); i++)
    {
      if (rem[i] > f) continue;
      ans = (ans + calc(rem[i], true)) % mod;
    }

    for (int bit = 0, end = 1 << rem.size(); bit < end; bit++)
    {
      if (__builtin_popcount(bit) <= 1 || __builtin_popcount(bit) > 3) continue;

      lli l = 1;
      for (int i = 0; i < rem.size(); i++)
        if (bit & (1 << i))
        {
          l = lcm(l, rem[i]);
          if (l > f) break;
        }
      bool toSkip = false;
      // for (int i = 0; i < hehe.size(); i++)
      //   if (bit & (1 << i))
      //     toSkip |= hehe[i] == l;
      if (l > f || toSkip) continue;
      // removed.insert(curr);
      DEBUG printf("\t\t%d - %lld - %lld\n", bit, l, calc(l));
      ans = (ans + (__builtin_popcount(bit) & 1 ? 1 : -1)*calc(l, true) % mod + mod) % mod;
    }
    printf("%lld\n", ans);
  }
  return 0;
}