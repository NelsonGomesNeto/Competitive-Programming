#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = LONG_LONG_MAX;

const int maxN = 2e5; int n; lli s;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d %lld", &n, &s);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    if (-*max_element(a, a+n) > s) printf("-1\n");
    else
    {
      int bestStart = -1, bestEnd = -1;
      lli delta = a[0];
      for (int i = 0, j = 0; i < n;)
      {
        while (j + 1 < n && -(delta + a[j + 1]) <= s)
        {
          delta += a[j + 1];
          j++;
        }

        if (-delta <= s && j - i + 1 > bestEnd - bestStart + 1)
          bestStart = i, bestEnd = j;

        if (-delta > s)
        {
          while (-delta > s && i < n)
          {
            delta -= a[i];
            i++;
          }
          if (i < n) delta += a[i];
        }
        else
        {
          delta -= a[i];
          i++;
          if (i < n) delta += a[i];
        }
      }

      printf("%d %d\n", bestStart + 1, bestEnd + 1);
    }
  }
  return 0;
}
