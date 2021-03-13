#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli n;
  while (~scanf("%lld", &n))
  {
    lli base = 1000;
    lli ans = 0, k = 1;
    while (n > 0)
    {
      n -= base;
      if (n >= 0)
        ans += n + 1;
      else
        break;
      n += base;
      base *= 1000;
      k++;
    }
    printf("%lld\n", ans);
  }
  return 0;
}