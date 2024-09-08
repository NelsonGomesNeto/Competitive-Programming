#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli a, b, c, k;
  while (scanf("%lld %lld %lld %lld", &a, &b, &c, &k) != EOF)
  {
    lli ans = min(a, k);
    k -= a;
    k -= b;
    if (k > 0) ans -= min(c, k);
    printf("%lld\n", ans);
  }
  return 0;
}