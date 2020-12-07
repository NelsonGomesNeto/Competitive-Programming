#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN];

void printArray()
{
  DEBUG
    for (int i = 0; i < n; i++)
      printf("%lld%c", a[i], i < n - 1 ? ' ' : '\n');
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d", &n);
      for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);

      lli ans = 0;
      for (int i = 0, j = 0; j < n;)
      {
        while (i < j && a[i] <= 0) i++;
        j = max(j, i + 1);
        while (j < n && a[j] >= 0) j++;
        if (j < n && a[i] > 0 && a[j] < 0)
        {
          lli gone = min(a[i], -a[j]);
          a[i] -= gone, a[j] += gone;
        }
      }
      printArray();

      for (int i = 0, j = n - 1; i < j;)
      {
        while (i < j && a[i] >= 0) i++;
        while (i < j && a[j] <= 0) j--;
        if (i < j && a[i] < 0 && a[j] > 0)
        {
          lli gone = min(-a[i], a[j]);
          ans += gone, a[i] += gone, a[j] -= gone;
        }
      }
      printArray();

      printf("%lld\n", ans);
      DEBUG printf("------------------\n");
    }
  return 0;
}