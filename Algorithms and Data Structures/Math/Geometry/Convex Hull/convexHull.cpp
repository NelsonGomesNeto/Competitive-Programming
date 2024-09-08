#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
  void print() { printf("%lld %lld\n", x, y); }
  double crossProduct(const Point& other) const { return x*other.y - y*other.x; }
  int orientation(const Point& b, const Point &c) const
  {
    lli sa = signedArea(b, c);
    if (sa < 0) return -1; // clockwise;
    else if (sa > 0) return 1; // counter-clockwise
    return 0; // collinear
  }
  lli signedArea(const Point& b, const Point& c) const { return x*(b.y - c.y) + b.x*(c.y - y) + c.x*(y - b.y); }
  lli squaredDistance(const Point& other) const { return (x - other.x)*(x - other.x) + (y - other.y)*(y - other.y); }
};

vector<Point> convexHull(vector<Point> &points, bool includeCollinear = false)
{
  // Left-bottom most;
  Point p0 = *min_element(points.begin(), points.end(), [](const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
  });
  sort(points.begin(), points.end(), [&p0](const Point& a, const Point& b) {
    int o = p0.orientation(a, b);
    if (o == 0) return p0.squaredDistance(a) < p0.squaredDistance(b);
    return o < 0;
  });

  vector<Point> ans;
  int allowedOrientation = includeCollinear ? 0 : -1;
  for (int i = 0; i < points.size(); i++)
  {
    while (ans.size() >= 2 && ans[ans.size() - 2].orientation(ans.back(), points[i]) > allowedOrientation)
      ans.pop_back();
    ans.push_back(points[i]);
  }

  return ans;
}


int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    vector<Point> points(n);
    for (int i = 0; i < n; i++)
      points[i].read();

    vector<Point> ch = convexHull(points);
    for (Point &p: ch)
      p.print();
  }
  return 0;
}