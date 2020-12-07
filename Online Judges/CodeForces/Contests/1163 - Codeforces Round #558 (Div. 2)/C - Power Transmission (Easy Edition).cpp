#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  To avoid precision erros, use the following line equation:
    a*x + b*y = c
    Where a = dy = (y2 - y1) and = b = dx = (x2 - x1)

  To cut out repeated lines, use map<Slope, set<int>> slopeMap
    Slope stores a and b
    Slope(a, b) is equivalent to Slope(a / gcd(a, b), b / gcd(a, b))
    if (a < 0 || (a == 0 && b < 0)) a *= -1, b *= -1;
    slopeMap[Slope(a, b)].insert(c)

  Now to count the intersections:
  count lines in slopeMap (just sum the sizes)
  for each s in slope:
    ans += (lines - s.size()) * s.size()
    (All c's inside s will represent a line that is parallel
    They will only intersect with every other line, excluding them, so:
    subtract them from the total lines and multiple by the amount of them)
*/

const int maxN = 1e3; int n;
struct Point { int x, y; };
Point points[maxN];
struct Slope
{
  int dy, dx;
  bool operator<(const Slope &s) const { return(dy < s.dy || (dy == s.dy && dx < s.dx)); }
  void simplify()
  {
    int g = gcd(dy, dx);
    dy /= g, dx /= g;
    if (dy < 0 || (dy == 0 && dx < 0)) dy *= -1, dx *= -1;
  }
};
map<Slope, set<int>> slopeMap;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d %d", &points[i].x, &points[i].y);

  lli ans = 0, lines = 0;
  for (int i = 0; i < n; i ++)
    for (int j = i + 1; j < n; j ++)
    {
      Slope slope = {points[i].y - points[j].y, points[i].x - points[j].x};
      slope.simplify();
      int c = slope.dy * points[i].x - slope.dx * points[i].y;
      if (!slopeMap[slope].count(c)) lines ++, slopeMap[slope].insert(c);
    }
  for (auto &i: slopeMap)
    ans += (lines - i.second.size()) * (lli) i.second.size();
  printf("%lld\n", ans >> 1);

  return(0);
}