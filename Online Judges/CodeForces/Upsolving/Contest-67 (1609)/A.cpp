#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 15; int n;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    sort(a, a+n);

    for (int i = 0; i < n; i++)
      if (a[i] % 2 == 0)
        for (int j = n - 1; j > i; j--)
          while (a[i] % 2 == 0)
          {
            a[i] /= 2, a[j] *= 2;
            sort(a, a+n);
          }

    bool changes = false;
    do
    {
      changes = false;
      for (int i = 0; i < n && !changes; i++)
        for (int j = n - 1; j >= 0 && !changes; j--)
          if (a[i] % 2 == 0 && i != j)
          {
            lli l = a[i], r = a[j];
            while (l % 2 == 0)
              l /= 2, r *= 2;
            if (l + r > a[i] + a[j])
              a[i] = l, a[j] = r, changes = true;
            sort(a, a+n);
          }
    }
    while (changes);

    lli ans = 0;
    for (int i = 0; i < n; i++) ans += a[i];
    printf("%lld\n", ans);
  }
  return 0;
}
