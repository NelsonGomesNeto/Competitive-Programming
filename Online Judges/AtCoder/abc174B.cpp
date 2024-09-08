#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; double d;
struct Point
{
  double x, y;
  void read() { scanf("%lf %lf", &x, &y); }
  double distance(Point other)
  {
    return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
  }
};
Point points[maxN];

int main()
{
  while (scanf("%d %lf", &n, &d) != EOF)
  {
    for (int i = 0; i < n; i++)
      points[i].read();

    int ans = 0;
    for (int i = 0; i < n; i++)
      if (points[i].distance({0, 0}) <= d)
        ans++;
    printf("%d\n", ans);
  }
  return 0;
}