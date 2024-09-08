#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli c, d; scanf("%lld %lld", &c, &d);
    lli delta = abs(c - d);
    int ans = 0;
    if (c == 0 && d == 0) ans = 0;
    else if (delta == 0) ans = 1;
    else if (delta & 1) ans = -1;
    else ans = 2;
    printf("%d\n", ans);
  }
  return 0;
}
