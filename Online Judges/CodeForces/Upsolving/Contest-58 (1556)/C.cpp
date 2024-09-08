#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  0123456789x
  (((()(()))(

  ()))(()(())))
*/

const int maxN = 1e3; int n;
lli c[maxN], acc[maxN + 1];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &c[i]);
      if (i & 1) c[i] *= -1;
      DEBUG printf("\t%d %lld\n", i, c[i]);
      acc[i + 1] = acc[i] + c[i];
    }

    lli ans = 0;
    lli open = 0;
    lli before = 0;
    for (int i = 0; i < n; i++)
      if (i & 1)
      {
        lli x = min(open, -c[i]);
        ans += x; // + (x > 1);
        open += c[i];
        if (open == 0)
        {
          before++;
          ans += before;
        }
        if (open < 0) open = 0;
      }
      else
      {
        open += c[i];
      }
    printf("%lld\n", ans);
  }
  return 0;
}
