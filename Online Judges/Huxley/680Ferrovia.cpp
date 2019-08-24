#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5 + 1; int n;
const double inf = 1e9;
struct Point
{
  double x, y;
  double distance(Point &p)
  {
    return sqrt((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
  }
  void normalize()
  {
    double norm = sqrt(x*x + y*y);
    x /= norm, y /= norm;
  }
  Point operator-(const Point &p)
  {
    return Point({x - p.x, y - p.y});
  }
  double operator*(const Point &p)
  {
    return x * p.x + y * p.y;
  }
  Point closestPoint(Point &p1, Point &p2)
  {
    Point v = p2 - p1, u = p1 - *this, w = p2 - *this;
    double vu = v * u, vv = v * v;
    double t = -vu / vv;
    // return pointBetween(t, p1, p2); if it's a line and not a segment
    if (t >= 0 && t <= 1) return pointBetween(t, p1, p2);
    return u*u <= w*w ? p1 : p2;
  }
  Point pointBetween(double t, Point &p1, Point &p2)
  {
    return Point({(1 - t) * p1.x + t * p2.x,
                  (1 - t) * p1.y + t * p2.y});
  }
  void print()
  {
    printf("%.4lf\n%.4lf\n", x, y);
    // printf("%.4lf %.4lf\n", x, y);
  }
};
Point station, points[maxN];

int main()
{
  while (scanf("%lf %lf", &station.x, &station.y) != EOF)
  {
    scanf("%d", &n);
    for (int i = 0; i < n + 1; i ++)
      scanf("%lf %lf", &points[i].x, &points[i].y);

    double d = inf; Point ans;
    for (int i = 0; i < n; i ++)
    {
      Point closest = station.closestPoint(points[i], points[i + 1]);
      double newD = station.distance(closest);
      if (newD < d)
        d = newD, ans = closest;
    }
    // station.print();
    ans.print();
  } 

  return(0);
}