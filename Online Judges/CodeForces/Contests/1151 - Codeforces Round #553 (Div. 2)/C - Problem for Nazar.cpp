#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const lli mod = 1e9 + 7;

lli nearestPowerOfTwo(lli number)
{
  lli p = 0;
  while (number) number >>= 1, p ++;
  return(p - 1);
}

lli start(lli power)
{
  lli s = power & 1 ? 2 : 1;
  while (power > 1)
  {
    s += 1LL << (power - 1);
    power -= 2;
  }
  return(s);
}

lli last(lli power)
{
  return(start(power) + 2*((1LL << power) - 1));
}

lli multMod(lli a, lli b)
{
  if (b == 1) return(a);
  lli res = multMod(a, b >> 1);
  res = (res + res) % mod; if (b & 1) res = (res + a) % mod;
  return(res);
}

lli powMod(lli x, lli n)
{
  if (!n) return(1);
  lli res = powMod(x, n >> 1);
  res = multMod(res, res); if (n & 1) res = multMod(res, x);
  return(res);
}

lli apSum(lli a1, lli an, lli n)
{
  DEBUG printf("ap %lld %lld %lld\n", a1, an, n);
  return(multMod(((multMod(n, a1) % mod) + multMod(n, an) % mod) % mod, powMod(2, mod - 2)));
}

int main()
{
  lli l, r; scanf("%lld %lld", &l, &r);
  lli pl = nearestPowerOfTwo(l), pr = nearestPowerOfTwo(r);
  lli sl = start(pl), sr = start(pr);
  lli ssl = sl + 2*(l - (1LL << pl)), ssr = sr + 2*(r - (1LL << pr));
  lli eel = last(pr - 1), eer = start(pl + 1);
  DEBUG printf("p %lld %lld\n", pl, pr);
  DEBUG printf("s %lld %lld\n", sl, sr);
  DEBUG printf("ss %lld %lld\n", ssl, ssr);
  DEBUG printf("ee %lld %lld\n", eel, eer);
  if (pl % 2 == pr % 2)
    printf("%lld\n", (apSum(ssr, ssl, ((ssr - ssl) >> 1LL) + 1) + (pl < pr ? apSum(eer, eel, ((eel - eer) >> 1LL) + 1) : 0)) % mod);
  else
  {
    lli lsum = apSum(ssl, eel, ((eel - ssl) >> 1LL) + 1), rsum = apSum(eer, ssr, ((ssr - eer) >> 1LL) + 1);
    DEBUG printf("sum %lld %lld\n", lsum, rsum);
    printf("%lld\n", pl < pr ? (lsum + rsum) % mod : (lsum));
  }
  return(0);
}