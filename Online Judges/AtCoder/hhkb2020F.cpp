#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
const lli mod = 1e9 + 7;
struct Interval
{
  lli l, r;
  void read() { scanf("%lld %lld", &l, &r); }
};
Interval intervals[maxN];

lli fat[maxN + 2];
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
lli apSum(lli a1, lli an, lli n)
{
  return(n * (a1 + an) % mod * inv(2) % mod);
}

int main()
{
  fat[0] = 1;
  for (int i = 1; i <= maxN + 1; i++)
    fat[i] = fat[i - 1] * i % mod;

  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      intervals[i].read();

    // Interval target = Interval{0, 0};
    // for (int i = 0; i < n; i++)
    //   if (intervals[i].l > target.l)
    //     target.l = intervals[i].l;

    // target.r = 1e9;
    // for (int i = 0; i < n; i++)
    //   if (target.l <= intervals[i].r)
    //     target.r = intervals[i].r;

    // lli e = apSum(target.l, target.r, target.r - target.l + 1);

    lli rl = 1;
    for (int i = 0; i < n; i++)
      rl = rl * (intervals[i].r - intervals[i].l) % mod;

    lli ans = 0;
    for (int k = 0; k < 1e4; k++)
    {
      lli now = 0;
      for (int i = 0; i < n; i++)
      {
        lli delta = rand() % (intervals[i].r - intervals[i].l + 1);
        now = max(now, intervals[i].l + delta);
      }
      lli e = now;
      ans = (ans + fat[n + 1] * e * rl % mod);
    }
    
    // printf("target interval: %lld %lld || %lld %lld\n", target.l, target.r, e, rl);
    printf("%lld\n", ans);
  }
  return 0;
}