#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int n;
struct Point
{
  long double x, y, angle;
  long double distance(Point &other) { return sqrt((x-other.x)*(x-other.x) + (y-other.y)*(y-other.y)); }
  void read() { scanf("%Lf %Lf", &x, &y); angle = atan2(y, x); }
  bool operator<(const Point &other) const { return angle < other.angle; }
  void operator+=(const Point &other) { x += other.x, y += other.y; }
};
Point points[maxN], origin = {0, 0};

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) points[i].read();
  sort(points, points+n);

  long double ans = 0;
  for (int i = 0; i < n; i ++)
  {
    Point at = origin;
    for (int a = 0, j = i; a < n; a ++, j = (j + 1) % n)
    {
      at += points[j];
      ans = max(ans, at.distance(origin));
    }
  }
  printf("%.15Lf\n", ans);

  return(0);
}