#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN]; lli target;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    target = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      target += a[i];
    }
    sort(a, a+n);
    if (target % n != 0)
    {
      printf("-1\n");
      continue;
    }
    target /= n;

    lli required = 0;
    for (int i = 0; i < n; i++)
      required += max(0LL, target - a[i]);

    DEBUG printf("\t%lld\n", required);

    int ans = 0;
    lli currSum = 0;
    while (ans < n && currSum != required)
    {
      currSum += a[n - ans - 1] - target;
      DEBUG printf("\t\t%lld\n", currSum);
      ans++;
    }

    if (currSum != required) printf("-1\n");
    else printf("%d\n", ans);
  }
  return 0;
}
