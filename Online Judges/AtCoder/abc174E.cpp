#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli k;
lli a[maxN];

bool can(lli x)
{
  lli cuts = 0;
  for (int i = 0; i < n; i++)
    if (a[i] > x)
      cuts += a[i] / x;
  return cuts <= k;
}

int main()
{
  while (scanf("%d %lld", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    lli lo = 1, hi = 1e9;
    while (lo < hi)
    {
      lli mid = (lo + hi) >> 1;
      if (can(mid)) hi = mid;
      else lo = mid + 1;
    }
    printf("%lld\n", lo);
  }
  return 0;
}