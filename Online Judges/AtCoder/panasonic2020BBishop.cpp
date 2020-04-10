#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli h, w;

int main()
{
  while (scanf("%lld %lld", &h, &w) != EOF)
  {
    lli ans = ((w >> 1LL) + (w & 1LL)) * ((h >> 1LL) + (h & 1LL));
    ans += (w >> 1LL) * (h >> 1LL);
    if (h == 1 || w == 1)
      ans = 1;
    printf("%lld\n", ans);
  }
  return 0;
}