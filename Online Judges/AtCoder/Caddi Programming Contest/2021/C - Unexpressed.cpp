#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli pot(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans *= x;
    x *= x, y >>= 1LL;
  }
  return ans;
}

int main()
{
  lli n;
  while (~scanf("%lld", &n))
  {
    lli ans = n;
    vector<lli> toRemove;
    for (lli a = 2, end = sqrt(n); a <= end; a++)
      for (lli b = 2; pot(a, b) <= n; b++)
        toRemove.push_back(pot(a, b));
    sort(toRemove.begin(), toRemove.end());
    toRemove.resize(distance(toRemove.begin(), unique(toRemove.begin(), toRemove.end())));

    printf("%lld\n", ans - toRemove.size());
  }
  return 0;
}