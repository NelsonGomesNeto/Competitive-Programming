#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 40; int n;
const long double EPS = 1e-7;
struct Point
{
  long double x, y;
  Point operator+(const Point &other) { return Point{x + other.x, y + other.y}; }
  Point operator-(const Point &other) { return Point{x - other.x, y - other.y}; }
  Point operator*(const long double a) { return Point{x * a, y * a}; }
  void read() { scanf("%Lf %Lf", &x, &y); }
  long double distance(Point &other) { return sqrt((x-other.x)*(x-other.x) + (y-other.y)*(y-other.y)); }
  long double cross(Point &other) { return x*other.y - y*other.x; }
};
struct Circle
{
  Point center; long double radious;
  bool contains(Point &p) { return center.distance(p) <= radious + EPS; }
};
Point points[maxN];
vector<Point> secondGroup;

Circle circumCircle(Point &a, Point &b, Point &c)
{
  Point u = Point{(b - a).y, (a - b).x};
  Point v = Point{(c - a).y, (a - c).x};
  Point n = (c - b) * 0.5;
  long double t = u.cross(n) / v.cross(u);
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
  int tt = 1;
  while (scanf("%d", &n) != EOF && n)
  {
    for (int i = 0; i < n; i ++)
      points[i].read();

    // The idea is to use 1 circle with 2 or 3 points, and the other covering all the other points
    long double ans = 1e9;
    for (int i = 0; i < n; i ++)
      for (int j = i + 1; j < n; j ++)
      {
        Circle a = Circle{(points[i] + points[j]) * 0.5, points[i].distance(points[j]) * 0.5};
        if (a.radious > ans) continue;
        secondGroup.clear();
        for (int k = 0; k < n; k ++)
          if (!a.contains(points[k]))
            secondGroup.push_back(points[k]);
        Circle b = minimumCircle(secondGroup);
        ans = min(ans, max(a.radious, b.radious));
      }
    for (int i = 0; i < n; i ++)
      for (int j = i + 1; j < n; j ++)
        for (int k = j + 1; k < n; k ++)
        {
          Circle a = circumCircle(points[i], points[j], points[k]);
          if (a.radious > ans) continue;
          secondGroup.clear();
          for (int m = 0; m < n; m ++)
            if (!a.contains(points[m]))
              secondGroup.push_back(points[m]);
          Circle b = minimumCircle(secondGroup);
          ans = min(ans, max(a.radious, b.radious));
        }

    printf("%.2Lf\n", ans);
  }
  return(0);
}