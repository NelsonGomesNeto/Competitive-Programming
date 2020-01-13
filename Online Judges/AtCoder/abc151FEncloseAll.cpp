#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n;
const ldouble EPS = 1e-12;

struct Point
{
  ldouble x, y;
  Point operator+(const Point &other) { return Point{x + other.x, y + other.y}; }
  Point operator-(const Point &other) { return Point{x - other.x, y - other.y}; }
  Point operator*(const ldouble a) { return Point{x * a, y * a}; }
  ldouble operator*(const Point &other) { return x * other.x + y * other.y; }
  ldouble distance(Point &p) { return sqrt((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y)); }
  ldouble cross(Point &other) { return x*other.y - y*other.x; }
  void normalize()
  {
    double norm = sqrt(x*x + y*y);
    x /= norm, y /= norm;
  }
  Point pointOfInterception(Point &p1, Point &p2)
  {
    Point v = p2 - p1, u = p1 - *this, w = p2 - *this;
    double vu = v * u, vv = v * v;
    double t = -vu / vv;
    // return pointBetween(t, p1, p2); if it's a line and not a segment
    if (t >= 0 && t <= 1) return vectorToSegment(t, p1, p2);
    return u*u <= w*w ? p1 : p2;
  }
  bool ccw(Point &B, Point &C)
  {
    return (C.y - this->y) * (B.x - this->x) > (B.y - this->y) * (C.x - this->x);
  }
  Point vectorToSegment(double t, Point &p1, Point &p2)
  {
    return Point({(1 - t) * p1.x + t * p2.x,
                  (1 - t) * p1.y + t * p2.y});
  }
  void print() { printf("%.4Lf %.4Lf\n", x, y); }
};
vector<Point> points;

struct Circle
{
  Point center; ldouble radious;
  bool contains(Point &p) { return center.distance(p) <= radious + EPS; }
};

Circle circumCircle(Point &a, Point &b, Point &c)
{
  Point u = Point{(b - a).y, (a - b).x};
  Point v = Point{(c - a).y, (a - c).x};
  Point n = (c - b) * 0.5;
  ldouble t = u.cross(n) / v.cross(u);
  Point center = ((a + c)*0.5) + v*t;
  return Circle{center, center.distance(a)};
}

Circle minimumCircle(vector<Point> &p)
{
  random_shuffle(p.begin(), p.end());
  Circle circle = Circle{p[0], 0};
  for (int i = 0; i < p.size(); i ++)
  {
    if (circle.contains(p[i])) continue;
    circle = Circle{p[i], 0};
    for (int j = 0; j < i; j ++)
    {
      if (circle.contains(p[j])) continue;
      circle = Circle{(p[j] + p[i])*0.5, p[j].distance(p[i])*0.5};
      for (int k = 0; k < j; k ++)
      {
        if (circle.contains(p[k])) continue;
        circle = circumCircle(p[j], p[i], p[k]);
      }
    }
  }
  return circle;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    points.resize(n);
    for (int i = 0; i < n; i ++)
      scanf("%Lf %Lf", &points[i].x, &points[i].y);

    Circle circle = minimumCircle(points);
    printf("%.15Lf\n", circle.radious);
  }
  return 0;
}