#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const double eps = 1;
struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
};
struct PointD
{
  double x, y;
  bool operator<(const PointD &other) const { return x < other.x || (x == other.x && y < other.y); }
  double dist(Point &other)
  {
    return abs(x - other.x) + abs(y - other.y);
  }
};
Point points[4];

double centerX = 0, centerY = 0;
double eval(double side, bool integer = false)
{
  vector<PointD> ps = {{centerX - side / 2, centerY - side / 2},
                       {centerX - side / 2, centerY + side / 2},
                       {centerX + side / 2, centerY - side / 2},
                       {centerX + side / 2, centerY + side / 2}};
  if (integer)
    ps = {{centerX - ceil(side / 2), centerY - ceil(side / 2)},
          {centerX - ceil(side / 2), centerY + floor(side / 2)},
          {centerX + floor(side / 2), centerY - ceil(side / 2)},
          {centerX + floor(side / 2), centerY +floor( side / 2)}};
  sort(ps.begin(), ps.end());
  double ans = 1e18;
  do
  {
    double total = 0;
    for (int i = 0; i < 4; i++)
    {
      if (integer) total += ceil(ps[i].dist(points[i]));
      else total += ps[i].dist(points[i]);
    }
    ans = min(ans, total);
  } while (next_permutation(ps.begin(), ps.end()));
  
  if (integer)
  {
    ps = {{centerX - floor(side / 2), centerY - floor(side / 2)},
          {centerX - floor(side / 2), centerY + ceil(side / 2)},
          {centerX + ceil(side / 2), centerY - floor(side / 2)},
          {centerX + ceil(side / 2), centerY +ceil( side / 2)}};
    sort(ps.begin(), ps.end());
    double ans = 1e18;
    do
    {
      double total = 0;
      for (int i = 0; i < 4; i++)
      {
        if (integer) total += ceil(ps[i].dist(points[i]));
        else total += ps[i].dist(points[i]);
      }
      ans = min(ans, total);
    } while (next_permutation(ps.begin(), ps.end()));
  }
  return ans;
}
lli ternarySearch()
{
  double lo = -1e12, hi = 1e12;
  while (abs(hi - lo) > eps)
  {
    double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    double evallo = eval(midlo), evalhi = eval(midhi);
    if (evallo < evalhi) lo = midlo;
    else if (evalhi < evallo) hi = midhi;
    else lo = midlo, hi = midhi;
  }
  lli ans = 1e18;
  lo = floor(lo) - 10, hi = ceil(hi) + 10;
  while (lo <= hi)
  {
    ans = min(ans, (lli)eval(lo, true));
    lo++;
  }
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    for (int i = 0; i < 4; i++)
      points[i].read();

    centerX = 0, centerY = 0;
    for (int i = 0; i < 4; i++)
      centerX += points[i].x, centerY += points[i].y;
    centerX /= 4, centerY /= 4;

    lli ans = ternarySearch();
    double baseX = floor(centerX), baseY = floor(centerY);
    for (int i = -2; i <= 4; i++)
      for (int j = -2; j <= 4; j++)
      {
        centerX = baseX + i, centerY = baseY + j;
        ans = min(ans, ternarySearch());
      }
    printf("%lld\n", ans);
  }
  return 0;
}
