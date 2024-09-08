#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
lli a[maxN];
lli ans[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);

    for (int k = 2; k <= n; k++)
    {
      lli best = LONG_LONG_MIN;
      for (int i = 0; i + k - 1 < n; i++)
      {
        lli now = 0;
        for (int j = 0; j < k; j++)
          for (int p = j + 1; p < k; p++)
            now += abs(a[i + j] - a[i + p]);
        best = max(best, now);
      }
      ans[k - 2] = best;
    }

    for (int i = 0; i + 1 < n; i++)
      printf("%lld%c", ans[i], i + 2 < n ? ' ' : '\n');
  }
  return 0;
}