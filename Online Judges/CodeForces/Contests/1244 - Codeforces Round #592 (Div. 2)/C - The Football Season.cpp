#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli n, p, w, d;
  while (scanf("%lld %lld %lld %lld", &n, &p, &w, &d) != EOF)
  {
    lli x = -1, y = 0;
    for (; y < w; y ++)
      if (p >= y * d && (p - (y * d)) % w == 0 && (p - (y * d)) / w + y <= n)
      {
        x = (p - (y * d)) / w;
        break;
      }
    if (x == -1) printf("-1\n");
    else printf("%lld %lld %lld\n", x, y, n - (x + y));
  }
  return 0;
}