#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli a, b;

lli binarySearch(lli lo = 1, lli hi = a / b + 10)
{
  while (lo < hi)
  {
    lli mid = (lo + hi) >> 1;
    DEBUG printf("\t\t\t%lld %lld | %lld | %lld\n", a, b, mid, a - mid*b);
    if (a - mid*b <= b) hi = mid;
    else lo = mid + 1;
  }
  return lo;
}

int main()
{
  while (~scanf("%lld %lld", &a, &b))
  {
    lli ans = 0;
    while (a != b)
    {
      if (b > a) swap(a, b);
      DEBUG printf("\t%lld %lld\n", a, b);
      if (a < 0 || b < 0) break;
      // a - x*b < b
      // a - (x + 1)*b > 0
      // (x + 1)*b > a
      // (x + 1) > a / b
      // x > a / b - 1
      // lli x = a / b - 2;
      lli x = binarySearch();
      DEBUG printf("\t\t%lld\n", x);
      ans += x;
      a = a - x * b;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
