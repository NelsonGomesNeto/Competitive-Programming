#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli r, x, y;
  while (~scanf("%lld %lld %lld", &r, &x, &y))
  {
    double d = sqrt(x*x + y*y);
    lli ans = ceil(d / r);
    if (r > d)
      ans = 2;
    printf("%lld\n", ans);
  }
  return 0;
}