#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli maxN = 5e5, maxB = 60; lli n;
const lli mod = 1e9 + 7;
lli x[maxN];
lli a[maxN], b[maxN];
lli cnt[64];

int main()
{
  lli t; scanf("%lld", &t);
  for (lli tt = 1; tt <= t; tt++)
  {
    scanf("%lld", &n);
    for (lli i = 0; i < n; i++)
      scanf("%lld", &x[i]);

    memset(cnt, 0, sizeof(cnt));
    for (lli bit = 0; bit < maxB; bit++)
      for (lli i = 0; i < n; i++)
        if ((x[i] >> bit) & 1LL)
          cnt[bit]++;

    for (lli i = 0; i < n; i++)
    {
      a[i] = 0;
      for (lli bit = 0; bit < maxB; bit++)
        if ((x[i] >> bit) & 1LL)
        {
          a[i] = (a[i] + cnt[bit] * ((1LL << bit) % mod) % mod) % mod;
          // for (lli j = 0; j < n; j++)
          //   a[i] = (a[i] + (x[i] & x[j])) % mod;
        }
    }
    for (lli i = 0; i < n; i++)
    {
      b[i] = 0;
      for (lli bit = 0; bit < maxB; bit++)
        if ((x[i] >> bit) & 1LL)
          b[i] = (b[i] + n * ((1LL << bit) % mod) % mod) % mod;
        else
        {
          b[i] = (b[i] + cnt[bit] * ((1LL << bit) % mod) % mod) % mod;
          // for (lli j = 0; j < n; j++)
          //   b[i] = (b[i] + (x[i] | x[j])) % mod;
        }
    }

    lli ans = 0;
    for (lli i = 0; i < n; i++)
      ans = (ans + a[i] * b[i] % mod) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}
