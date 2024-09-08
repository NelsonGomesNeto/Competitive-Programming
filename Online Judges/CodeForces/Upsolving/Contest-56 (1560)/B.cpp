#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli a, b, c; scanf("%lld %lld %lld", &a, &b, &c);
    if (a > b) swap(a, b);
    lli dist = b - a;

    lli n = 2 * dist;
    lli ans = -1;
    if (n >= b && n >= c)
    {
      ans = c + dist;
      if (ans > n) ans = c - dist;
      if (ans < 1) ans = -1;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
