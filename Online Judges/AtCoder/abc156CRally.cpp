#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
const lli inf = 1e18;
int x[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%d", &x[i]);

    lli ans = inf;
    for (int p = 1; p <= 100; p ++)
    {
      lli c = 0;
      for (int i = 0; i < n; i ++)
        c += (x[i] - p)*(x[i] - p);
      ans = min(ans, c);
    }
    printf("%lld\n", ans);
  }
  return 0;
}