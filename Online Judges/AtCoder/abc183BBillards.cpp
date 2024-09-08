#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const double eps = 1e-7;
struct Point
{
  double x, y;
  bool read() { return scanf("%lf %lf", &x, &y) != EOF; }
};
Point s, g;

bool can(double x)
{
  double slope = s.y / (x - s.x);
  double to = slope * (g.x - x);
  // printf("%lf %lf %lf %d\n", x, slope, to, to >= g.y);
  return to <= g.y;
}
double binarySearch(double lo = s.x, double hi = g.x)
{
  while (abs(hi - lo) > eps)
  {
    double mid = (lo + hi) / 2;
    if (can(mid)) hi = mid;
    else lo = mid;
  }
  return hi;
}

int main()
{
  while (s.read())
  {
    g.read();
    double ans = binarySearch();
    printf("%.15lf\n", ans);
  }
  return 0;
}