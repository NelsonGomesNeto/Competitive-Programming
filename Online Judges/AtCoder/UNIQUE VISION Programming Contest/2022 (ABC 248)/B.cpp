#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli a, b, k;
  while (~scanf("%lld %lld %lld", &a, &b, &k))
  {
    lli ans = 0;
    while (a < b)
      a *= k, ++ans;
    printf("%lld\n", ans);
  }
  return 0;
}