#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  Notice that the answer has a lower and an upper limit:
    Suppose x is inf:
      x will be clipped down by any f of type 2 (max(x, a))
      From there on:
        It will always be the maximum value possible i.e. upper limit
    The lower limit follows the same idea, but with -inf

    Notice that if there's no f of type 2 or 3, it won't have any limits
      But we don't need to treat these cases differently, since the upper limit
      will just be inf by following above's strategy.

    We can calculate the upper and lower limits by choosing a big value
    for x (1e9 is enough).
      if t[i] == 1: add a to maximumLimit and minimumLimit
      if t[i] == 2: maximumLimit and minimumLimit must be at most a
      if t[i] == 3: maximumLimit and minimumLimit must be at least a

  Now we just need to know what will happen in between the limits.
    As soon as x blows a superior limit (from a type 2 function):
      It will be the same as the maximumLimit
    Similarly if it blows the inferior limit

    Otherwise, it will just grow with type 1 function until it
    blows something.

  So, instead of only:
    if t[i] == 1: add a to maximumLimit and minimumLimit
  We should also calculate the totalSum:
    if t[i] == 1: add a to maximumLimit, minimumLimit and totalSum
*/

const int maxN = 2e5; int n, q;
const lli inf = 1e9;
lli a[maxN], t[maxN], x[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    lli maximumLimit = inf, minimumLimit = -inf, base = 0;
    for (int i = 0; i < n; i++)
      scanf("%lld %lld", &a[i], &t[i]);

    for (int i = 0; i < n; i++)
    {
      if (t[i] == 1)
        base += a[i], maximumLimit += a[i], minimumLimit += a[i];
      else if (t[i] == 2)
        maximumLimit = max(maximumLimit, a[i]), minimumLimit = max(minimumLimit, a[i]);
      else
        maximumLimit = min(maximumLimit, a[i]), minimumLimit = min(minimumLimit, a[i]);
    }

    scanf("%d", &q);

    for (int i = 0; i < q; i++)
      scanf("%lld", &x[i]);

    for (int i = 0; i < q; i++)
    {
      lli ans = max(minimumLimit, min(maximumLimit, x[i] + base));
      printf("%lld\n", ans);
    }
  }
  return 0;
}
