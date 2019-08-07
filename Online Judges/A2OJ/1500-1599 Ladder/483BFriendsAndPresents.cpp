#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli c1, c2, x, y;

lli binarySearch(lli lo, lli hi)
{
  if (lo >= hi) return(lo);
  lli mid = (lo + hi) >> 1;
  lli a = mid - (mid / x), b = mid - (mid / y);
  // printf("%lld %lld %lld - %lld\n", a, b, c, mid);
  if (a >= c1 && b >= c2 && mid - (mid / lcm(x, y)) >= c1 + c2) return(binarySearch(lo, mid));
  return(binarySearch(mid + 1, hi));
}

int main()
{
  scanf("%lld %lld %lld %lld", &c1, &c2, &x, &y);
  printf("%lld\n", binarySearch(2, 1e18));
  return(0);
}