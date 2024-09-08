#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli a, b; scanf("%lld %lld", &a, &b);
    if (a == b) printf("0 0\n");
    else
    {
      lli delta = abs(a - b);

      lli aa = a % delta, bb = b % delta;
      lli minMove = min(max(aa, bb), max(delta - bb, delta - aa));
      printf("%lld %lld\n", delta, minMove);
    }
  }
  return 0;
}
