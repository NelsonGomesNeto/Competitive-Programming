#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const double pi = acos(-1);

int n;
struct Point
{
  double x, y;
  void read() { scanf("%lf %lf", &x, &y); }
  void print() { printf("%.15lf %.15lf\n", x, y); }
  Point operator+(Point &other) { return Point{x + other.x, y + other.y}; }
  Point operator-(Point &other) { return Point{x - other.x, y - other.y}; }
  Point operator/(double k) { return Point{x / k, y / k}; }
  Point operator*(double k) { return Point{x * k, y * k}; }
  double distance(Point &other)
  {
    return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
  }
};
Point p0, pmid;

int main()
{
  while (~scanf("%d", &n))
  {
    p0.read();
    pmid.read();

    Point center = (p0 + pmid) / 2;
    double angle = 2*pi / n;
    Point p0CenterVector = p0 - center;
    double p0Angle = atan2(p0CenterVector.y, p0CenterVector.x);

    double p1Angle = p0Angle + angle;

    Point p1Edge = Point{cos(p1Angle), sin(p1Angle)};
    p1Edge = p1Edge * center.distance(p0);
    Point p1 = center + p1Edge;
    p1.print();
  }
  return 0;
}