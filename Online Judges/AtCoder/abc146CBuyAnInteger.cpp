#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli a, b, x;

lli d(lli n)
{
  lli ans = n == 0;
  while (n) ans ++, n /= 10LL;
  return ans;
}
lli f(lli n)
{
  return a * n + b * d(n);
}

lli binarySearch(lli lo = 0, lli hi = 1e9)
{
  while (lo < hi)
  {
    lli mid = (lo + hi + 1) >> 1LL;
    if (f(mid) <= x) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main()
{
  while (scanf("%lld %lld %lld", &a, &b, &x) != EOF)
  {
    lli ans = binarySearch();
    printf("%lld\n", ans);
  }
  return 0;
}