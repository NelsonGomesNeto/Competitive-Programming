#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli s, i, e; scanf("%lld %lld %lld", &s, &i, &e);
    lli lo = 0, hi = e + 1;
    while (lo < hi)
    {
      lli mid = (lo + hi) >> 1LL;
      if (s + mid > i + (e - mid)) hi = mid;
      else lo = mid + 1;
    }
    printf("%lld\n", e - lo + 1);
  }
  return(0);
}
