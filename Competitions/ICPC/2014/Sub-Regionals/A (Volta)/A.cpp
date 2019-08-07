#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli x, y;
lli binarySearch(lli lo, lli hi)
{
  if (lo >= hi) return(lo);
  lli mid = (lo + hi) >> 1;
  lli b = ceil((double) (x * mid) / y);
  if (mid > b) return(binarySearch(lo, mid));
  return(binarySearch(mid + 1, hi));
}

int main()
{
  scanf("%lld %lld", &x, &y);
  lli ans = binarySearch(1, 1e6);
  printf("%lld\n", ans);
  return(0);
}