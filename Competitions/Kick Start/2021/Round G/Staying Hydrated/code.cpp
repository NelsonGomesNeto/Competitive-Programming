#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxK = 1e5; int k;
struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
};
Point p[2][maxK];
lli minX, maxX;
lli minY, maxY;

lli evalY(lli x, lli y)
{
  lli totalDist = 0;
  for (int i = 0; i < k; i++)
    if (y < p[0][i].y || p[1][i].y < y)
      totalDist += min(abs(y - p[0][i].y), abs(y - p[1][i].y));
  return totalDist;
}
lli findY(lli x)
{
  lli loy = minY, hiy = maxY;
  while (hiy - loy >= 3)
  {
    lli midlo = (2*loy + hiy) / 3, midhi = (loy + 2*hiy) / 3;
    lli elo = evalY(x, midlo), ehi = evalY(x, midhi);
    if (elo <= ehi) hiy = midhi;
    else loy = midlo;
  }
  lli best = LONG_LONG_MAX, y;
  for (lli yy = loy; yy <= hiy; yy++)
  {
    lli e = evalY(x, yy);
      if (e < best)
        best = e, y = yy;
  }
  return y;
}
lli evalX(lli x)
{
  lli totalDist = 0;
  for (int i = 0; i < k; i++)
    if (x < p[0][i].x || p[1][i].x < x)
      totalDist += min(abs(x - p[0][i].x), abs(x - p[1][i].x));
  return totalDist;
}
lli findX()
{
  lli lox = minX, hix = maxX;
  while (hix - lox >= 3)
  {
    lli midlo = (2*lox + hix) / 3, midhi = (lox + 2*hix) / 3;
    lli elo = evalX(midlo), ehi = evalX(midhi);
    if (elo <= ehi) hix = midhi;
    else lox = midlo;
  }
  lli best = LONG_LONG_MAX, x;
  for (lli xx = lox; xx <= hix; xx++)
  {
    lli e = evalX(xx);
    if (e < best)
      best = e, x = xx;
  }
  return x;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
      p[0][i].read(), p[1][i].read();
    minX = p[0][0].x, maxX = p[1][0].x;
    minY = p[0][0].y, maxY = p[1][0].y;
    for (int i = 0; i < k; i++)
    {
      minX = min(minX, p[0][i].x), maxX = max(maxX, p[1][i].x);
      minY = min(minY, p[0][i].y), maxY = max(maxY, p[1][i].y);
    }

    lli x = findX();
    lli y = findY(x);
    DEBUG printf("\t%lld\n", evalY(x, y));
    printf("Case #%d: %lld %lld\n", tt, x, y);
  }
  return 0;
}