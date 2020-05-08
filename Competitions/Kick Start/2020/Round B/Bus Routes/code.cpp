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
    int n; lli d; scanf("%d %lld", &n, &d);
    lli x[n]; for (int i = 0; i < n; i++) scanf("%lld", &x[i]);

    lli curr = d;
    for (int i = n - 1; i >= 0; i--)
    {
      lli m = curr / x[i];
      DEBUG printf("\t%lld %lld - %lld\n", curr, m, m * x[i]);
      curr = m * x[i];
    }

    printf("Case #%d: %lld\n", tt, curr);
  }
  return 0;
}