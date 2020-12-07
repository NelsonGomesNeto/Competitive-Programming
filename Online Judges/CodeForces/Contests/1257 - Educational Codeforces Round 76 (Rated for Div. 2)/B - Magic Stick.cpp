#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli x, y; scanf("%lld %lld", &x, &y);
    bool can = x >= y;
    while (!can)
    {
      x = !(x & 1LL) ? 3LL*x >> 1LL : x - 1;
      can = x >= y;
      // printf("\t%lld %lld\n", x, y);
      if (x <= 2) break;
    }
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
