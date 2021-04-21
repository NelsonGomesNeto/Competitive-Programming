#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const double pi = acosl(-1), eps = 1e-11;

struct Point
{
  double x, y, mag, angle;
  void read()
  {
    scanf("%lf %lf", &x, &y);
  }
  Point operator-(const Point &other)
  {
    Point res = Point{x - other.x, y - other.y};
    res.mag = res.getMag();
    res.angle = res.getAngle();
    return res;
  }
  double getAngle() { return atan2(y, x); }
  double getMag() { return sqrt(x*x + y*y); }
};
Point points[maxN + 1], vectors[maxN];
// 43 44 45

double eval(double a)
{
  double total = 0;
  for (int i = 0; i < n; i++)
  {
    double aa = a + vectors[i].angle;
    while (aa > pi) aa -= 2*pi;
    while (aa < -pi) aa += 2*pi;
    // printf("\t%lf %lf\n", aa, cos(aa));
    if (aa <= pi / 2 && aa >= -pi / 2)
    {
      double c = cos(a + vectors[i].angle);
      total += vectors[i].mag * c;
    }
  }
  return total;
}
double ternarySearch(double lo, double hi)
{
  lo -= eps, hi += eps;
  while (abs(hi - lo) > eps)
  {
    double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    double elo = eval(midlo), ehi = eval(midhi);
    if (elo < ehi) hi = midhi;
    else if (ehi < elo) lo = midlo;
    else lo = midlo, hi = midhi;
  }
  // printf("%lf %lf - %lf %lf\n", lo, hi, eval(lo), eval(hi));
  return eval((lo + hi) / 2);
  return min(eval(lo), eval(hi));
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      points[i].read();
    points[n] = points[0];
    for (int i = 1; i <= n; i++)
      vectors[i - 1] = points[i] - points[i - 1];

    DEBUG {
      for (double a = 0; a < pi; a += pi / 8)
      {
        double total = eval(a);
        printf("angle %lf: %lf\n", a, total);
      }
    }

    // double ans = 1e18;
    // int t = 8;
    // for (double a = 0; a < 2*pi; a += 2*pi / t)
    //   ans = min(ans, ternarySearch(a, a + 2*pi/t));

    double ans = min(ternarySearch(0, pi), ternarySearch(0, 2*pi));
    printf("%.2lf\n", ans);
  }
  return 0;
}