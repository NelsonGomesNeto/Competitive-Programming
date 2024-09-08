#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n;

struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
  bool operator<(const Point &other) const { return x < other.x || (x == other.x && y < other.y); }
};
set<Point> has;
map<pair<int, int>, int> cntv, cnth;
Point points[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    has.clear();
    cntv.clear();
    cnth.clear();
    for (int i = 0; i < n; i++)
    {
      points[i].read();
      has.insert(points[i]);
    }

    int vertical = 0;
    int horizontal = 0;
    int other = 0;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
      {
        if (points[i].x == points[j].x)
        {
          pair<int, int> curr = make_pair(points[i].y, abs(points[i].y - points[j].y));
          // vertical += cntv[curr];
          cntv[curr]++;
        }
        else if (points[i].y == points[j].y)
        {
          pair<int, int> curr = make_pair(points[i].x, abs(points[i].x - points[j].x));
          // horizontal += cnth[curr];
          cnth[curr]++;
        }
        else
        {
          int minx = min(points[i].x, points[j].x);
          int miny = min(points[i].y, points[j].y);
          int dx = abs(points[i].x - points[j].x);
          int dy = abs(points[i].y - points[j].y);
          bool valid = true;
          for (int x = 0; x < 2; x++)
            for (int y = 0; y < 2; y++)
              valid = valid && has.count(Point{minx + x*dx, miny + y*dy});
          other += valid;
        }
      }
    int ans = (vertical >> 1) + (horizontal >> 1) + (other >> 1);
    printf("%d\n", ans);
  }
  return 0;
}