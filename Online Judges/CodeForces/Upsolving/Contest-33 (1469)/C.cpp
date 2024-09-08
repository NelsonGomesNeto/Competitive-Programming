#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli k;
lli h[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &k);
    for (int i = 0; i < n; i++)
      scanf("%lld", &h[i]);

    bool can = true;
    lli minHeight = h[0], maxHeight = h[0] + k - 1;
    for (int i = 1; i < n; i++)
    {
      minHeight = minHeight - (k - 1);
      if (minHeight < h[i])
        minHeight = h[i];

      maxHeight = maxHeight + (k - 1);
      if (maxHeight - (k - 1) > h[i] + k - 1)
        maxHeight = h[i] + k - 1 + k - 1;

      if (minHeight > h[i] + (k - 1) || maxHeight - (k - 1) < h[i])
        can = false;
      DEBUG printf("\t%lld - %lld %lld - %d\n", h[i], minHeight, maxHeight, can);
    }
    if (minHeight > h[n - 1] || maxHeight - (k - 1) < h[n - 1])
      can = false;
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
