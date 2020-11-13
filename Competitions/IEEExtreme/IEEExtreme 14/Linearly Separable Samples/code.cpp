#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const double inf = 1e6, eps = 1e-6, pi = acos(-1);
struct Point
{
  double x, y, ang;
  bool operator==(const Point &other) { return x == other.x && y == other.y; }
  Point operator-(const Point &other) { return Point{x - other.x, y - other.y}; }
  double cross(Point other) { return x * other.y - y * other.x; }
  bool operator<(const Point &other) const { return ang < other.ang; }
};
vector<Point> points[2];
double minX[2], maxX[2], minY[2], maxY[2];

Point getP(double ang)
{
  return Point{cos(ang), sin(ang)};
}
int eval(Point a)
{
  Point vec = a;
  int s[2] = {0, 0}, ss[2] = {0, 0};
  for (int i = 0; i < 2; i++)
    for (Point &p: points[i])
    {
      double res = vec.cross(a - p);
      if (abs(res) <= eps) s[i]++, ss[i]++;
      else if (res > 0)
      {
        if (i) s[i]++;
        else ss[i]++;
      }
      else if (res < 0)
      {
        if (!i) s[i]++;
        else ss[i]++;
      }
    }
  return max(ss[0] + ss[1], s[0] + s[1]);
}
int ternarySearch(double lo = 0, double hi = 2*pi)
{
  while (abs(hi - lo) > eps)
  {
    double mlo = (2*lo + hi) / 3, mhi = (lo + 2*hi) / 3;
    int elo = eval(getP(mlo)), ehi = eval(getP(mhi));
    if (elo > ehi) hi = mhi;
    else if (ehi > elo) lo = mlo;
    else lo = mlo, hi = mhi;
  }
  return max(eval(getP(hi)), eval(getP(lo)));
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);

    points[0].clear(), points[1].clear();
    minX[0] = minX[1] = minY[0] = minY[1] = inf;
    maxX[0] = maxX[1] = maxY[0] = maxY[1] = -inf;
    for (int i = 0; i < n; i++)
    {
      double x, y; int k; scanf("%lf %lf %d", &x, &y, &k);
      // int xxx, xx, yyy, yy, k; scanf("%d.%d %d.%d %d", &xxx, &xx, &yyy, &yy, &k);
      // double x = xxx * 100 + xx, y = yyy * 100 + yy;
      double ang = atan2(y, x);
      // if (ang < 0) ang += 2*pi;
      points[k > 0].push_back(Point{x, y, ang});
      minX[k > 0] = min(minX[k > 0], x);
      maxX[k > 0] = max(maxX[k > 0], x);

      minY[k > 0] = min(minY[k > 0], y);
      maxY[k > 0] = max(maxY[k > 0], y);
    }

    vector<Point> corners[2];
    for (int i = 0; i < 2; i++)
    {
      sort(points[i].begin(), points[i].end());
      // corners[i].push_back(Point{minX[i], minY[i]});
      // corners[i].push_back(Point{maxX[i], minY[i]});
      // corners[i].push_back(Point{maxX[i], maxY[i]});
      // corners[i].push_back(Point{minX[i], maxY[i]});
      if (!points[i].empty())
      {
        corners[i].push_back(points[i][0]);
        corners[i].push_back(points[i].back());
      }
    }

    Point origin = {0, 0};
    bool can = false;
    for (int j = 0; j < 2; j++)
      for (Point &a: corners[j])
      {
        Point b = origin;
        // if (a == b) continue;

        // line: a, b
        Point vec = getP(a.ang);
        can |= eval(vec) == points[0].size() + points[1].size();
      }
    int res = ternarySearch();
    // printf("%d\n", res);
    can |= res == points[0].size() + points[1].size();

    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}