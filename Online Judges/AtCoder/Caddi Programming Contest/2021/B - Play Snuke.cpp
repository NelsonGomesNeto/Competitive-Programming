#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = LONG_LONG_MAX;

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    lli a, p, x;
    lli ans = inf;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld %lld %lld", &a, &p, &x);
      lli inStock = x - a;
      if (inStock > 0)
        ans = min(ans, p);
    }
    if (ans == inf)
      ans = -1;
    printf("%lld\n", ans);
  }
  return 0;
}