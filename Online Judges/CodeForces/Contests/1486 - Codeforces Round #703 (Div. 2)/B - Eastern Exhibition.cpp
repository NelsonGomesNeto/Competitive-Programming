#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
  lli distance(lli ox, lli oy) { return abs(x - ox) + abs(y - oy); }
};
Point points[maxN];

lli evalY(lli x, lli y)
{
  lli total = 0;
  for (int i = 0; i < n; i++)
    total += points[i].distance(x, y);
  return total;
}
lli ternarySearchY(lli x)
{
  lli lo = 0, hi = 1e9;
  while (abs(hi - lo) >= 10)
  {
    lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
    lli elo = evalY(x, midlo), ehi = evalY(x, midhi);
    if (elo < ehi) hi = midhi;
    else lo = midlo;
  }
  lli minX = lo, minXeval = evalY(x, lo);
  for (int i = lo; i <= hi; i++)
  {
    lli now = evalY(x, i);
    if (now < minXeval)
      minXeval = now, minX = i;
  }
  return minX;
}
lli evalX(lli x)
{
  return evalY(x, ternarySearchY(x));
}
lli ternarySearchX()
{
  lli lo = 0, hi = 1e9;
  while (abs(hi - lo) >= 10)
  {
    lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
    lli elo = evalX(midlo), ehi = evalX(midhi);
    if (elo < ehi) hi = midhi;
    else lo = midlo;
  }
  lli minX = lo, minXeval = evalX(lo);
  for (int i = lo; i <= hi; i++)
  {
    lli now = evalX(i);
    if (now < minXeval)
      minXeval = now, minX = i;
  }
  return minX;
}

lli binarySearchX(lli x, bool upperBound)
{
  lli target = evalX(x);
  lli lo = upperBound ? x : 0, hi = upperBound ? 1e9 : x;
  while (lo < hi)
  {
    lli mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (evalX(mid) == target) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (evalX(mid) == target) hi = mid;
      else lo = mid + 1;
    }
  }
  return lo;
}
lli binarySearchY(lli x, lli y, bool upperBound)
{
  lli target = evalY(x, y);
  lli lo = upperBound ? y : 0, hi = upperBound ? 1e9 : y;
  while (lo < hi)
  {
    lli mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (evalY(x, mid) == target) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (evalY(x, mid) == target) hi = mid;
      else lo = mid + 1;
    }
  }
  return lo;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      points[i].read();

    lli minX = ternarySearchX();
    lli loX = binarySearchX(minX, false), hiX = binarySearchX(minX, true);

    lli minY = ternarySearchY(minX);
    lli loY = binarySearchY(minX, minY, false), hiY = binarySearchY(minX, minY, true);
    lli ans = (hiX - loX + 1) * (hiY - loY + 1);
    DEBUG printf("\t%lld %lld | %lld %lld\n", loX, hiX, loY, hiY);
    printf("%lld\n", ans);
  }
  return 0;
}
