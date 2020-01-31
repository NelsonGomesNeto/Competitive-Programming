#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli n, d;

bool can(lli x)
{
  return x + (d / (x + 1) + (d % (x + 1) != 0)) <= n;
}
lli binSearch(lli lo = 0, lli hi = n)
{
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
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%lld %lld", &n, &d);
    lli x = binSearch();
    printf("%s\n", x + (d / (x + 1) + (d % (x + 1) != 0)) <= n ? "YES" : "NO");
  }
  return 0;
}
