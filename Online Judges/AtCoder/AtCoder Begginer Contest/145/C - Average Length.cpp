#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8; int n;
struct Point
{
  ldouble x, y;
  void read() { scanf("%Lf %Lf", &x, &y); }
  ldouble dist(Point &other)
  {
    return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
  }
  bool operator<(const Point &other) const
  {
    return x < other.x || (x == other.x && y < other.y);
  }
};
Point points[maxN];

ldouble fat(ldouble x)
{
  if (x <= 1) return 1;
  return x * fat(x - 1);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      points[i].read();
    sort(points, points+n);

    ldouble ans = 0;
    do
    {
      for (int i = 1; i < n; i ++)
        ans += points[i - 1].dist(points[i]);
    } while (next_permutation(points, points+n));
    ans /= fat(n);
    printf("%.15Lf\n", ans);
  }
  return 0;
}
