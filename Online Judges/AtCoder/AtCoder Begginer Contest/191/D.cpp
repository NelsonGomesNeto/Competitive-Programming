#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Point
{
  ldouble x, y;
  ldouble dist(Point &other) { return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y)); }
  ldouble dist2(Point &other) { return (x - other.x)*(x - other.x) + (y - other.y)*(y - other.y); }
};

const ldouble inf = 1e9;
const ldouble eps = 1e-6;
ldouble cx, cy, r;
Point center;

bool valid(lli x, lli y)
{
  Point curr = {(ldouble)x, (ldouble)y};
  return curr.dist2(center) <= r * r || abs(r * r - curr.dist2(center)) <= eps;
}
lli binarySearch(lli y)
{
  lli base = ceill(cx);
  lli lo = base, hi = inf;
  while (lo < hi)
  {
    lli x = (lo + hi + 1) >> 1;
    if (valid(x, y)) lo = x;
    else hi = x - 1;
  }
  return valid(lo, y) ? lo - base + 1 : 0;
}
lli binarySearch2(lli y)
{
  lli base = floorl(cx) - (ceill(cx) == floorl(cx));
  lli lo = -inf, hi = base;
  while (lo < hi)
  {
    lli x = (lo + hi) >> 1;
    if (valid(x, y)) hi = x;
    else lo = x + 1;
  }
  return valid(lo, y) ? base - lo + 1 : 0;
}

int main()
{
  while (~scanf("%Lf %Lf %Lf", &cx, &cy, &r))
  {
    center = Point{cx, cy};
    lli ans = 0;
    for (lli y = cy - r; y <= cy + r; y++)
    {
      ans += binarySearch(y);
      ans += binarySearch2(y);
    }
    printf("%lld\n", ans);
  }
  return 0;
}