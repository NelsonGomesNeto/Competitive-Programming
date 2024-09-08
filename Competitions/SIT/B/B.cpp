#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
  bool operator<(const Point &other) const { return x < other.x || (x == other.x && y < other.y); }
};
set<Point> points;
int dx[4] = {0, 1, 0, 1};
int dy[4] = {0, 0, 1, 1};

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    points.clear();
    for (int i = 0; i < 3; i++)
    {
      Point a; a.read();
      points.insert(a);
    }

    int xdelta = 0, ydelta = 0;
    int minx = 1e6, miny= 1e6;
    for (Point i: points)
      for (Point j: points)
      {
        xdelta = max(xdelta, abs(i.x - j.x));
        ydelta = max(ydelta, abs(i.y - j.y));
        minx = min(minx, i.x);
        miny = min(miny, i.y);
      }

    Point base = {minx, miny};
    Point ans;
    for (int k = 0; k < 4; k++)
    {
      Point a = {base.x + xdelta*dx[k], base.y + ydelta*dy[k]};
      if (!points.count(a))
        ans = a;
    }
    printf("%d %d\n", ans.x, ans.y);
  }
  return 0;
}