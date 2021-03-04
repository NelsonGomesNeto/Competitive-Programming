#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n;
int a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli u, v;
    scanf("%d", &n);
    scanf("%lld %lld", &u, &v);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    lli ans = 1e18;
    for (int i = 1; i < n; i++)
    {
      if (abs(a[i] - a[i - 1]) >= 2)
        ans = 0;
      else if (abs(a[i] - a[i - 1]) == 1)
        ans = min({ans, u, v});
      else
      {
        ans = min({ans, 2*v, u + v});
        if (i - 2 >= 0 && abs(a[i - 2] - a[i - 1]) != 0)
          ans = min(ans, u);
        if (i + 1 < n && abs(a[i + 1] - a[i]) != 0)
          ans = min(ans, u);
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
