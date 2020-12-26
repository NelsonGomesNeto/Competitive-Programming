#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli k;
lli a[maxN], f[maxN];
lli af[maxN + 1];

bool can(lli x)
{
  lli cost = 0;
  for (int i = 0; i < n; i ++)
    if (a[i] * f[i] > x)
      cost += a[i] - x / f[i];
  return cost <= k;
}

lli binarySearch()
{
  lli lo = 0, hi = 1e12 + 5;
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
  scanf("%d %lld", &n, &k);
  for (int i = 0; i < n; i ++)
    scanf("%lld", &a[i]);
  for (int i = 0; i < n; i ++)
    scanf("%lld", &f[i]);
  sort(a, a+n, greater<lli>()), sort(f, f+n);

  lli ans = binarySearch();
  printf("%lld\n", ans);

  return 0;
}