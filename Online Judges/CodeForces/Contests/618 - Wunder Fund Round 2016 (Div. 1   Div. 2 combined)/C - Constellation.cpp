#include <bits/stdc++.h>
using namespace std;
const double inf = 1e24;

struct Point
{
  double x, y, d; int id;
  double dist(const Point &a) { return(sqrt((a.x - x)*(a.x - x) + (a.y - y)*(a.y - y))); }
  bool collinear(const Point &a, const Point &b) { return((x - a.x)*(a.y - b.y) - (a.x - b.x)*(y - a.y) == 0); }
};
bool byX(const Point &a, const Point &b) { return(a.x < b.x); }
struct Ans
{
  int u, v; double d;
  bool operator<(const Ans &a) const { return(d < a.d); }
};
const int maxN = 1e5; int n;
Point points[maxN];

Ans bruteForce(int lo, int hi)
{
  Ans ans = {0, 0, inf};
  for (int i = lo; i <= hi; i ++)
    for (int j = i + 1; j <= hi; j ++)
    {
      double dist = points[i].dist(points[j]);
      if (dist < ans.d) ans = {i, j, dist};
    }
  return(ans);
}

Ans minMid(Ans &d, int lo, int hi)
{
  int mid = (lo + hi) >> 1;
  int begin = mid - 1, end = mid + 1;
  while (begin > lo && (points[mid].x - points[begin].x) < d.d) begin --;
  while (end < hi && (points[end].x - points[mid].x) < d.d) end ++;
  return(bruteForce(begin, end));
}

Ans findClosestPair(int lo, int hi)
{
  if  (hi - lo + 1 <= 3) return(bruteForce(lo, hi));

  int mid = (lo + hi) >> 1;
  Ans dlo = findClosestPair(lo, mid), dhi = findClosestPair(mid, hi);
  Ans d = min(dlo, dhi);

  return(min(d, minMid(d, lo, hi)));
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%lf %lf", &points[i].x, &points[i].y);
    points[i].id = i;
  }
  sort(points, points+n, byX);
  Ans ans = findClosestPair(0, n - 1);

  Point a = points[ans.u], b = points[ans.v], c = {0, 0, inf};
  Point midPoint = {(a.x + b.x) / 2.0, (a.y + b.y) / 2.0};
  for (int i = 0; i < n; i ++)
  {
    if (points[i].id == a.id || points[i].id == b.id || a.collinear(b, points[i])) continue;
    double d = midPoint.dist(points[i]);
    if (d < c.d) { c = points[i]; c.d = d; }
  }
  printf("%d %d %d\n", a.id + 1, b.id + 1, c.id + 1);

  return(0);
}