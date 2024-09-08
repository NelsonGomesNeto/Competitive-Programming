#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

lli k, l, r, t, x, y;

bool can(lli toAdd)
{
  lli newk = k + toAdd;
  newk -= t * x;
  return newk >= l;
}

int main()
{
  while (~scanf("%lld %lld %lld %lld %lld %lld", &k, &l, &r, &t, &x, &y))
  {
    bool can = false;
    set<lli> mods;
    if (k + y <= r) k += y;

    for (lli d = 0; d < t;)
    {
      lli lo = 0, hi = t - d;
      while (lo < hi)
      {
        lli mid = (lo + hi + 1) >> 1LL;
        if (k - mid*x >= l + (x > y ? x - y : 0)) lo = mid;
        else hi = mid - 1;
      }
      if (lo == 0)
      {
        break;
      }
      d += lo;
      if (d == t)
      {
        can = true;
        break;
      }

      lli m = (k - lo*x) - l;
      if (mods.count(m))
      {
        can = true;
        break;
      }
      mods.insert(m);

      k -= lo*x;
      k += y;
      DEBUG printf("\t%lld - %lld\n", d, k);
      if (k > r) break;
    }

    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}
