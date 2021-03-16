#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  miners:
    (0, y)
  diamonds:
    (x, 0)
*/

struct Point
{
  double x, y;
  void read() { scanf("%lf %lf", &x, &y); }
  double distance(Point &other) { return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y)); }
};
const int maxN = 1e5; int n;
double miners[maxN], diamonds[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    int mi = 0, di = 0;
    for (int i = 0; i < 2*n; i++)
    {
      double x, y; scanf("%lf %lf", &x, &y);
      if (x == 0)
        miners[mi++] = abs(y);
      else
        diamonds[di++] = abs(x);
    }

    sort(miners, miners+n);
    sort(diamonds, diamonds+n);

    double ans = 0;
    for (int i = 0, j = n - 1; i < n; i++, j--)
    {
      Point a = Point{0, miners[i]}, b = Point{diamonds[j], 0};
      ans += a.distance(b);
    }
    double ans2 = 0;
    for (int i = 0, j = 0; i < n; i++, j++)
    {
      Point a = Point{0, miners[i]}, b = Point{diamonds[j], 0};
      ans2 += a.distance(b);
    }
    printf("%.15lf\n", min(ans, ans2));
  }
  return 0;
}
