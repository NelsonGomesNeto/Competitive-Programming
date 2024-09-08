#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 4e5; int n;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    lli ans = 0;
    if (n == 1)
    {
      ans = a[0];
    }
    else
    {
      ans = a[0] + a[n - 1];
      for (int i = 1; i < n; i++)
        ans += abs(a[i] - a[i - 1]);

      if (n > 1 && a[0] > a[1]) ans -= a[0] - a[1];
      for (int i = 1; i + 1 < n; i++)
      {
        if (a[i] > a[i - 1] && a[i] > a[i + 1])
          ans -= a[i] - max(a[i - 1], a[i + 1]);
      }
      if (n > 1 && a[n - 1] > a[n - 2]) ans -= a[n - 1] - a[n - 2];
    }

    printf("%lld\n", ans);
  }
  return 0;
}
