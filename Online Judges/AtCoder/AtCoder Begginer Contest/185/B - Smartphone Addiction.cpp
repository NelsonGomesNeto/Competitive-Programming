#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli n; int m; lli t;
  while (~scanf("%lld %d %lld", &n, &m, &t))
  {
    bool can = true;
    lli battery = n;
    lli prv = 0;
    for (int i = 0; i < m; i++)
    {
      lli a, b; scanf("%lld %lld", &a, &b);
      // a *= 2; b *= 2;
      battery -= a - prv;
      if (battery <= 0) can = false;
      battery = min(n, battery + b - a);
      prv = b;
    }
    battery -= t - prv;
    if (battery <= 0) can = false;

    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}