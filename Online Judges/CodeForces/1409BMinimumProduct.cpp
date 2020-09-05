#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli solve(lli a, lli b, lli x, lli y, lli n)
{
  lli toRemove = min(a - x, n);
  n -= toRemove, a -= toRemove;
  b -= min(n, b - y);
  return a * b;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 0; tt < t; tt++)
    {
      lli a, b, x, y, n; scanf("%lld %lld %lld %lld %lld", &a, &b, &x, &y, &n);

      lli ans = min(solve(a, b, x, y, n), solve(b, a, y, x, n));

      printf("%lld\n", ans);
    }
  return 0;
}