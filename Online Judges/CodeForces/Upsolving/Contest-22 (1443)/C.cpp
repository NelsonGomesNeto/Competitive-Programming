#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
const lli inf = 1e9;
lli a[maxN], b[maxN];

lli memo[maxN];
bool can(lli maxt)
{
  lli s = 0;
  for (int i = 0; i < n; i++)
    if (a[i] > maxt)
      s += b[i];
  return s <= maxt;
}
lli bs(lli lo = 0, lli hi = inf)
{
  while (lo < hi)
  {
    lli mid = (lo + hi) >> 1LL;
    if (can(mid)) hi = mid;
    else lo = mid + 1;
  }
  return lo;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 0; tt < t; tt++)
    {
      scanf("%d", &n);
      for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
      for (int i = 0; i < n; i++)
        scanf("%lld", &b[i]);

      lli ans = bs();
      printf("%lld\n", ans);
    }
  return 0;
}
