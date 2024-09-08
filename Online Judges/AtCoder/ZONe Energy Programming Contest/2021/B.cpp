#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n, D, H;
const double eps = 1e-7;
int d[maxN], h[maxN];

bool can(double y)
{
  double a = (double)(H - y) / D;
  for (int i = 0; i < n; i++)
  {
    // printf("%lf - %lf - %d\n", a, d[i]*a + y, h[i]);
    if (d[i]*a + y < h[i])
      return false;
  }
  return true;
}

int main()
{
  while (~scanf("%d %d %d", &n, &D, &H))
  {
    for (int i = 0; i < n; i++)
      scanf("%d %d", &d[i], &h[i]);

    // printf("%d\n", can(3));
    double lo = 0, hi = 1000;
    while (abs(hi - lo) > eps)
    {
      double mid = (lo + hi) / 2;
      if (can(mid)) hi = mid;
      else lo = mid;
    }
    printf("%.15lf\n", lo);
  }
  return 0;
}