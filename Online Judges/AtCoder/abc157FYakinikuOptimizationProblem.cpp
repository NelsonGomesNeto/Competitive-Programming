#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  We will cook meat[i] iff dist(p, meat[i])*c <= T
  We can rewrite it as: dist(p, meat[i]) <= T / c, which
  is the same as saying that p is inside circle(center: meat[i], radious: T/c)

  So, we can use a binary search and find the minimum T in which
  there's a point inside at least K circles (from meats)

  That point will be either the center of a circle or the intersection
  of two circles (so we can test in O(n^3))
*/

const int maxN = 60; int n, k;
const double eps = 1e-7;

struct Point
{
  double x, y;
  Point operator+(const Point &other) { return Point{x + other.x, y + other.y}; }
  Point operator-(const Point &other) { return Point{x - other.x, y - other.y}; }
  Point operator*(const double a) { return Point{x * a, y * a}; }
  double operator*(const Point &other) { return x * other.x + y * other.y; }
  double distance(Point &other) { return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y)); }
  double cross(Point &other) { return x*other.y - y*other.x; }
  Point rotate(double rad) { return Point{x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)}; }
  Point normalized()
  {
    double norm = sqrt(x*x + y*y);
    return Point{x / norm, y / norm};
  }
  void read() { scanf("%lf %lf", &x, &y); }
  void print() { printf("(%3.3lf, %3.3lf)\n", x, y); }
};
struct Circle
{
  Point center; double radious;
  bool contains(Point &p) { return center.distance(p) <= radious + eps; }
  pair<Point, Point> circleIntersections(Circle &other)
  {
    double d = center.distance(other.center);
    double u = acos((other.radious*other.radious + d*d - radious*radious) / (2.0*other.radious*d));
    Point dc = (center - other.center).normalized() * other.radious;
    return pair<Point, Point>
    {
      other.center + dc.rotate(u),
      other.center + dc.rotate(-u)
    };
  }
};
struct Meat
{
  Point p; double c;
  void read() { p.read(); scanf("%lf", &c); }
  Circle getCircle(double T) { return Circle{p, T / c}; }
};
Meat meats[maxN];
Circle circles[maxN];

bool valid(Point &a)
{
  int done = 0;
  for (int i = 0; i < n; i++)
    done += circles[i].contains(a);
  return done >= k;
}
bool can(double T)
{
  for (int i = 0; i < n; i++)
    circles[i] = meats[i].getCircle(T);

  for (int i = 0; i < n; i++)
  {
    if (valid(meats[i].p))
      return true;

    for (int j = i + 1; j < n; j++)
    {
      pair<Point, Point> intersections = circles[i].circleIntersections(circles[j]);
      if (valid(intersections.first) || valid(intersections.second))
        return true;
    }
  }
  return false;
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      meats[i].read();

    double lo = 0, hi = 1e6;
    while (abs(hi - lo) > eps)
    {
      double mid = (lo + hi) / 2;
      if (can(mid)) hi = mid;
      else lo = mid;
    }
    printf("%lf\n", lo);
  }
  return 0;
}