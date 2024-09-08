#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    lli x, y, a, b; scanf("%lld %lld %lld %lld", &x, &y, &a, &b);
    if (x > y) swap(x, y);
    lli ans = x * min(b, 2*a) + (y - x) * a;
    printf("%lld\n", ans);
  }
  return 0;
}
