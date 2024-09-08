#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli a, b, c, d;
  while (scanf("%lld %lld %lld %lld", &a, &b, &c, &d) != EOF)
  {
    lli ans = max({a * c, a * d, b * c, b * d});
    printf("%lld\n", ans);
  }
  return 0;
}