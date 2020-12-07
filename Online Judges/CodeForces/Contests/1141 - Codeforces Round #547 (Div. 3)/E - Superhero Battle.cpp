#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; lli h; int n;
lli d[maxN], acc[maxN + 1];

int main()
{
  while (scanf("%lld %d", &h, &n) != EOF)
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &d[i]);
      d[i] *= -1;
    }

    int roundOneKill = -1;
    lli biggestPrefix = 0;
    for (int i = 0; i < n; i++)
    {
      acc[i + 1] = acc[i] + d[i];
      if (acc[i + 1] >= h)
      {
        roundOneKill = i + 1;
        break;
      }
      biggestPrefix = max(biggestPrefix, acc[i + 1]);
    }

    if (roundOneKill != -1) printf("%d\n", roundOneKill);
    else if (acc[n] <= 0) printf("-1\n");
    else
    {
      lli ans = (lli)n * ((h - biggestPrefix) / acc[n]);
      h -= (h - biggestPrefix) / acc[n] * acc[n];
      DEBUG printf("\t%lld - %lld - %lld\n", acc[n], biggestPrefix, h);
      while (h > 0)
        for (int i = 0; i < n && h > 0; i++)
        {
          ans++, h -= d[i];
          DEBUG printf("\t%lld - %lld\n", ans, h);
        }
      printf("%lld\n", ans);
    }
  }
  return 0;
}