#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n; lli m;
lli v[maxN];

bool can(lli x)
{
  lli moms = 0;
  for (int i = 0; i < n; i ++)
    moms += v[i] / x;
  return(moms >= m);
}

lli binarySearch(lli lo = 0, lli hi = 1e9)
{
  if (lo >= hi) return(lo);
  lli mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
  if (can(mid)) return(binarySearch(mid, hi));
  return(binarySearch(lo, mid - 1));
}

int main()
{
  scanf("%d %lld", &n, &m);
  for (int i = 0; i < n; i ++) scanf("%lld", &v[i]);
  sort(v, v+n);

  lli ans = binarySearch();
  printf("%lld\n", ans);

  return(0);
}