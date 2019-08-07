#include <bits/stdc++.h>
using namespace std;
struct Point
{
  double x, y;
  bool operator<(const Point &a) const { return(x < a.x); }
  double dist(Point &a) { return((a.x - x)*(a.x - x) + (a.y - y)*(a.y - y)); }
};
const int maxN = 1e4; int n;
Point points[maxN];

double bruteForce(int lo, int hi)
{
  double minDist = 1e18;
  for (int i = lo; i <= hi; i ++)
    for (int j = i + 1; j <= hi; j ++)
      minDist = min(minDist, points[i].dist(points[j]));
  return(minDist);
}

double minMid(double d, int lo, int hi)
{
  int mid = (lo + hi) >> 1;
  int begin = mid - 1, end = mid + 1;
  while (begin > lo && (points[mid].x - points[begin].x) < d) begin --;
  while (end < hi && (points[end].x - points[mid].x) < d) end ++;
  return(bruteForce(begin, end));
}

double dq(int lo, int hi)
{
  if (hi - lo + 1 <= 3) return(bruteForce(lo, hi));

  int mid = (lo + hi) >> 1;
  double dlo = dq(lo, mid), dhi = dq(mid, hi);
  double d = min(dlo, dhi);

  return(min(d, minMid(d, lo, hi)));
}

int main()
{
  while (scanf("%d", &n) && n)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lf %lf", &points[i].x, &points[i].y);

    sort(points, points+n);
    double minDist = sqrt(dq(0, n - 1));
    if (minDist < 1e4) printf("%.4lf\n", minDist);
    else printf("INFINITY\n");
  }
  return(0);
}