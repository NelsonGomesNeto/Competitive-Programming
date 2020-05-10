#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int x, y, a, b, c;
lli reds[maxN], greens[maxN], bugs[maxN];

int main()
{
  while (scanf("%d %d %d %d %d", &x, &y, &a, &b, &c) != EOF)
  {
    for (int i = 0; i < a; i++) scanf("%lld", &reds[i]);
    for (int i = 0; i < b; i++) scanf("%lld", &greens[i]);
    for (int i = 0; i < c; i++) scanf("%lld", &bugs[i]);
    sort(reds, reds+a, greater<lli>());
    sort(greens, greens+b, greater<lli>());
    sort(bugs, bugs+c, greater<lli>());
    reverse(reds, reds+x);
    reverse(greens, greens+y);

    lli ans = 0;
    for (int i = 0; i < x; i++) ans += reds[i];
    for (int i = 0; i < y; i++) ans += greens[i];
    for (int r = 0, g = 0, i = 0; i < c; i++)
    {
      lli dr = r < x ? bugs[i] - reds[r] : -1, dg = g < y ? bugs[i] - greens[g] : -1;
      DEBUG printf("%d %d %d - %lld %lld %lld\n", i, r, g, dr, dg, ans);
      if (dr > 0 && dr > dg)
        ans += dr, r++;
      else if (dg > 0)
        ans += dg, g++;
    }

    printf("%lld\n", ans);
  }
  return 0;
}