#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, q;
lli a[maxN];

int main()
{
  while (~scanf("%d %d", &n, &q))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    for (int qq = 0; qq < q; qq++)
    {
      int i; lli x; scanf("%d %lld", &i, &x); i--;

      a[i] *= x;

      lli g = a[0];
      for (i = 1; i < n; i++)
        g = gcd(g, a[i]);

      printf("%lld\n", g);
    }
  }
  return 0;
}
