#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1000, maxX = 1001; int n;
struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
  bool operator<(const Point &other) const { return x < other.x || (x == other.x && y < other.y); }
};
Point points[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
      points[i].read();
    sort(points, points+n);

    Point now = {0, 0};
    string ans = "";
    bool can = true;
    for (int i = 0; i < n; i ++)
    {
      while (now.x != points[i].x)
        ans += 'R', now.x ++;
      if (now.y > points[i].y)
      {
        can = false;
        break;
      }
      while (now.y != points[i].y)
        ans += 'U', now.y ++;
    }
    if (can) printf("YES\n%s\n", ans.c_str());
    else printf("NO\n");
  }
  return 0;
}
