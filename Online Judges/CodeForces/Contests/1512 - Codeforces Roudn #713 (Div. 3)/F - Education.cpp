#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli c;
lli a[maxN], b[maxN];

lli ceilDiv(lli num, lli div)
{
  return num / div + (num % div != 0);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &c);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < n - 1; i++)
      scanf("%lld", &b[i]);

    lli ans = ceilDiv(c, a[0]);
    lli days = 0, money = 0;
    for (int i = 0; i < n; i++)
    {
      ans = min(ans, days + ceilDiv(c - money, a[i]));

      if (i < n - 1)
      {
        lli addDays = b[i] - money > 0 ? ceilDiv(b[i] - money, a[i]) : 0;
        days += addDays + 1;
        money += addDays * a[i] - b[i];
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
