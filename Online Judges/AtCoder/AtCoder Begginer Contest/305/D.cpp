#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n, q;
lli a[maxN], acc[maxN + 1];

int main()
{
  int tt = 0;
  while (~scanf("%d", &n))
  {
    if (tt++) printf("---------------------\n");

    for (int i = 0; i < n; ++i)
      scanf("%lld", &a[i]);
    for (int i = 2; i < n; ++i)
      acc[i + 1] = acc[i] + (~i & 1 ? a[i] - a[i - 1] : 0);

    scanf("%d", &q);
    for (int qq = 1; qq <= q; ++qq)
    {
      int lo, hi;
      scanf("%d %d", &lo, &hi);

      int lp = lower_bound(a, a + n, lo) - a;
      int rp = upper_bound(a, a + n, hi) - a - 1;

      lli ans = lp == rp ? 0 : acc[rp + 1] - acc[lp + 1];
      if (~lp & 1) ans += a[lp] - lo;
      if (rp & 1) ans += hi - a[rp];
      DEBUG printf("[%d : %d] -- [%d : %d] -- %lld %lld\n", lo, hi, lp, rp, a[lp], a[rp]);
      printf("%lld\n", ans);
    }
  }
  return 0;
}
