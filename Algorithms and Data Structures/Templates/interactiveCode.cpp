#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    lli lo, hi; scanf("%lld %lld", &lo, &hi);
    while (lo < hi)
    {
      lli mid = (lo + hi) >> 1LL;
      printf("? %lld\n", mid); fflush(stdout);
      char response[3] = "lo";
      scanf(" %s", response);
      if (response[0] == '=') lo = hi = mid;
      else if (response[0] == '>') lo = mid + 1;
      else hi = mid - 1;
    }
    printf("! %lld\n", lo); fflush(stdout);
  }
  return 0;
}