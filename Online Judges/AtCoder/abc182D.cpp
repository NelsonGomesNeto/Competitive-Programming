#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];
lli acc[maxN + 1];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
      acc[i + 1] = acc[i] + a[i];

    lli ans = 0, curr = 0;
    int biggestPrv = -1;
    for (int i = 0; i < n; i++)
    {
      if (biggestPrv != -1)
      {
        curr += acc[biggestPrv + 1];
        ans = max(ans, curr);
        curr += acc[i + 1] - acc[biggestPrv + 1];
      }
      else
        curr += acc[i + 1];

      DEBUG printf("\t%d - %lld | %d\n", i, curr, biggestPrv);

      ans = max(ans, curr);

      if (biggestPrv == -1 || acc[i + 1] >= acc[biggestPrv + 1])
        biggestPrv = i;
    }
    printf("%lld\n", ans);
  }
  return 0;
}