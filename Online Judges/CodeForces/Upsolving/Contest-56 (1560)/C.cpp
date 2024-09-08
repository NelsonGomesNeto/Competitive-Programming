#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
1 2 5 10 17
1 3 5 7 9 ...
1 4 9 16
*/

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli k; scanf("%lld", &k);
    lli lo = 1, hi = 1e9;
    while (lo < hi)
    {
      lli mid = (lo + hi + 1) >> 1LL;
      if (mid * mid <= k) lo = mid;
      else hi = mid - 1;
    }

    lli c = lo + 1;
    printf("%lld\n", c);
  }
  return 0;
}
