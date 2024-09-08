#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli apSum(lli a1, lli n, lli q)
{
  return (a1+a1+(n-1)*q)*n / 2LL;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli l, r; scanf("%lld %lld", &l, &r);
    lli ans = 0;
    bool switched = r > l;
    if (switched) swap(l, r);

    lli lo = 0, hi = 2e9;
    while (lo < hi)
    {
      lli mid = (lo + hi + 1) >> 1LL;
      if (l - apSum(1, mid, 1) >= r) lo = mid;
      else hi = mid - 1;
    }
    ans += lo;
    l -= apSum(1, lo, 1);

    if (l == r) switched = false;

    lo = 0, hi = 2e9;
    while (lo < hi)
    {
      lli mid = (lo + hi + 1) >> 1LL;
      if (max(l, r) - apSum(ans + 1, (mid + 1) >> 1LL, 2) >= 0
        && min(l, r) - apSum(ans + 2, mid >> 1LL, 2) >= 0) lo = mid;
      else hi = mid - 1;
    }

    if (l >= r)
      l -= apSum(ans + 1, (lo + 1) >> 1LL, 2), r -= apSum(ans + 2, lo >> 1LL, 2);
    else
      r -= apSum(ans + 1, (lo + 1) >> 1LL, 2), l -= apSum(ans + 2, lo >> 1LL, 2);
    ans += lo;

    if (switched) swap(l, r);

    // lli curr = ans + 1;
    // while (curr <= l || curr <= r)
    // {
    //   if (l >= r) l -= curr;
    //   else r -= curr;
    //   curr++, ans++;
    // }

    printf("Case #%d: %lld %lld %lld\n", tt, ans, l, r);
  }
  return 0;
}