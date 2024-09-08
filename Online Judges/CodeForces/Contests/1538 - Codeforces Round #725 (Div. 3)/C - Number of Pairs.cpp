#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, l, r;
int a[maxN];

int binarySearch(int target, bool upperBound)
{
  int lo = 0, hi = n - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (a[mid] <= target) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (a[mid] >= target) hi = mid;
      else lo = mid + 1;
    }
  }
  if (upperBound) return a[lo] <= target ? lo : -1;
  else return a[lo] >= target ? lo : -1;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; ++tt)
  {
    scanf("%d %d %d", &n, &l, &r);
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);
    sort(a, a+n);

    lli ans = 0;
    for (int i = 0; i < n; ++i)
    {
      // a[i] + a[j] >= l
      // a[j] >= l - a[i]
      int loj = binarySearch(l - a[i], false);
      // a[i] + a[j] <= r
      // a[j] <= r - a[i]
      int hij = binarySearch(r - a[i], true);
      DEBUG printf("\t%d %d - %d %d - %d %d\n", i, a[i], loj, a[loj], hij, a[hij]);
      if (loj != -1 & hij != -1)
      {
        ans += hij - loj + 1;
        ans -= 2*a[i] >= l && 2*a[i] <= r;
      }
    }
    ans >>= 1;
    printf("%lld\n", ans);
  }
  return 0;
}
