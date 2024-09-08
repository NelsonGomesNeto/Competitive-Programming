#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const ldouble pi = acosl(-1);
const ldouble pi2 = pi / 2;
const ldouble eps = 1e-10;
ldouble radToDeg(ldouble angle) { return angle * 180 / pi; }
struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
  ldouble dist(const Point &other) { return sqrtl((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y)); }
  Point operator-(const Point &other) { return Point{x - other.x, y - other.y}; }
  ldouble dot(const Point &other) { return x*other.x + y*other.y; }
  ldouble mag() const { return sqrtl(x*x + y*y); }
  ldouble angle(const Point &other)
  {
    ldouble res = atan2l(x*other.y - y*other.x, dot(other));
    if (res < 0) res += 2*pi;
    return res;
  }
};
Point points[2*maxN];
double acc[2*maxN + 1];

bool valid(Point &u, int i, int j)
{
  int k = j + 1;

  Point v = points[k] - points[j];
  DEBUG printf("\t\t(%lld, %lld) - (%lld, %lld)\n", u.x, u.y, v.x, v.y);
  ldouble angle = u.angle(v);
  DEBUG printf("\t%d %d - %Lf - %Lf\n", j, k, angle, radToDeg(angle));

  if (angle >= pi2 || abs(angle - pi2) <= eps)
    return false;

  return true;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      points[i].read();
      points[n + i] = points[i];
    }
    for (int i = 0; i < 2*n; i++)
      acc[i + 1] = acc[i] + points[i].dist(points[(i + 1) % (2*n)]);

    for (int i = 0; i < n; i++)
    {
      ldouble ans = 0;
      Point u = points[(i + 1) % n] - points[i];
      // ans += points[i].dist(points[(i + 1) % n]);

      int lo = 0, hi = n - 1;
      while (lo < hi)
      {
        int mid = (lo + hi + 1) >> 1;
        if (valid(u, i, i + mid)) lo = mid;
        else hi = mid - 1;
      }
      DEBUG printf("\t%d %d\n", i, lo);
      ans += acc[i + lo + 1] - acc[i];

      // for (int j = (i + 1) % n, a = 0; a < n; a++)
      // {
      //   int k = (j + 1) % n;

      //   Point v = points[k] - points[j];
      //   DEBUG printf("\t\t(%lld, %lld) - (%lld, %lld)\n", u.x, u.y, v.x, v.y);
      //   ldouble angle = u.angle(v);
      //   DEBUG printf("\t%d %d - %Lf - %Lf\n", j, k, angle, radToDeg(angle));
      //   if (angle >= pi2 || abs(angle - pi2) <= eps)
      //     break;

      //   ans += points[j].dist(points[k]);

      //   j = k;
      // }

      printf("%.15Lf\n", ans);
    }
  }
  return 0;
}