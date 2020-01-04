#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    lli minR = 1e9, maxL = 1;
    for (int i = 0; i < n; i ++)
    {
      lli l, r; scanf("%lld %lld", &l, &r);
      minR = min(minR, r), maxL = max(maxL, l);
    }

    lli ans = max(0LL, maxL - minR);
    printf("%lld\n", ans);
  }
  return 0;
}
