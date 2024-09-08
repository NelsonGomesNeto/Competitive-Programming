#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

//a * b > 1e18
// a > 1e18 / b
const lli limit = 1000000000000000000LL;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    lli ans = 1, a;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a);
      if (a == 0)
      {
        ans = 0;
        continue;
      }
      if (ans > limit / a)
        ans = -1;
      else if (ans != -1)
        ans *= a;
      if (ans > limit)
        ans = -1;
    }
    printf("%lld\n", ans);
  }
  return 0;
}