#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli apSum(lli a1, lli n, lli d)
{
  lli an = a1 + (n - 1)*d;
  return n * (a1 + an) >> 1LL;
}

const int maxN = 1e5; int n; lli k;
lli a[maxN];

int main()
{
  while (~scanf("%d %lld", &n, &k))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    sort(a, a+n, greater<lli>());
    lli ans = 0;
    for (int i = 0; k > 0 && a[0] > 0; i += i < n)
    {
      int j = i;
      // while (j + 1 < n && a[j + 1] == a[0]) j++;

      lli cnt = j + 1;

      lli nxt = 0;
      if (j + 1 < n) nxt = a[j + 1];

      lli dist = a[0] - nxt;
      DEBUG printf("\t%d %lld %lld - %lld\n", j, dist, cnt, k);
      if (k <= cnt)
      {
        ans += a[0] * k;
        k = 0;
        break;
      }
      else
      {
        if (k < dist * cnt)
        {
          lli lo = 0, hi = dist;
          while (lo < hi)
          {
            lli mid = (lo + hi + 1) >> 1LL;
            if (mid * cnt <= k) lo = mid;
            else hi = mid - 1;
          }

          dist = lo;
          i -= (i != n - 1);
        }
        else
          i = j;

        DEBUG printf("\t\t%lld\n", dist);

        lli sum = apSum(a[0], dist, -1);
        ans += sum * cnt;
        k -= dist * cnt;
        a[0] -= dist;
      }
    }
    assert(a[0] >= 0);

    printf("%lld\n", ans);
  }
  return 0;
}