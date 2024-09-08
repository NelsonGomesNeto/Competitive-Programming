#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli L;
struct Glass
{
  lli a, b, h;
  void read() { scanf("%lld %lld %lld", &a, &b, &h); }
  lli liters(lli filledH)
  {
    return a * b * filledH;
  }
};
Glass glasses[maxN];

lli neededLiters(lli h)
{
  lli totalLiters = 0;
  for (int i = 0; i < n; i++)
  {
    if (glasses[i].h < h)
      return LONG_LONG_MAX;

    totalLiters += glasses[i].liters(h);
  }

  return totalLiters;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &L);
    for (int i = 0; i < n; i++) glasses[i].read();

    lli lo = 0, hi = L;
    while (lo < hi)
    {
      lli mid = (lo + hi + 1) >> 1;
      if (neededLiters(mid) <= L) lo = mid;
      else hi = mid -1;
    }
    lli rem = L - neededLiters(lo);
    assert(rem >= 0);

    printf("%lld %lld\n", lo, rem);
  }
  return 0;
}