#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n, n2; lli k;
lli a[maxN];

bool can(lli x)
{
  lli spent = 0;
  for (int i = n - 1; i >= n2; i --)
    if (a[i] < x)
      spent += x - a[i];
  return(spent <= k);
}

lli binarySearch(lli lo = 0, lli hi = 2e9)
{
  while (lo < hi)
  {
    lli mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
    if (can(mid)) lo = mid;
    else hi = mid - 1;
  }
  return(lo);
}

int main()
{
  while (scanf("%d %lld", &n, &k) != EOF)
  {
    n2 = n >> 1;
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);
    sort(a, a+n);

    lli ans = binarySearch();
    printf("%lld\n", ans);
  }
  return(0);
}
