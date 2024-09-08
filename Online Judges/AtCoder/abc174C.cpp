#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli k;

int main()
{
  while (scanf("%lld", &k) != EOF)
  {
    bool can = false;
    lli ans, pot = 7, sum = 0;
    for (ans = 1; ans < 1e7; ans++, pot = pot * 10 % k)
    {
      sum = (sum + pot % k) % k;
      if (sum == 0)
      {
        can = true;
        break;
      }
    }
    if (!can) ans = -1;
    printf("%lld\n", ans);
  }
  return 0;
}