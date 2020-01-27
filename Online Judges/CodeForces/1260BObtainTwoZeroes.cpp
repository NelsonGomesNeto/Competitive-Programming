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
    lli a, b; scanf("%lld %lld", &a, &b);
    if ((a + b) % 3 != 0) printf("NO\n");
    else
    {
      lli x = a - (4 * a - 2 * b) / 3, y = (2 * a - b) / 3;
      if (x >= 0 && y >= 0) printf("YES\n");
      else printf("NO\n");
    }
  }
  return 0;
}
