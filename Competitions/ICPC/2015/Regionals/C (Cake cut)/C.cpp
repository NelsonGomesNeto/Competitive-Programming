#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/*
Area of convex polygon:
            |x_1 y_1|
            |x_2 y_2|
1/2 * "det"(|...    |)
            |x_n y_n|
            |x_1 y_1|
*/

const int maxN = 1e5;
const lli inf = 1e18; int n;
struct Point
{
  lli x, y;
  lli cross(Point &p)
  {
    return(x*p.y - y*p.x);
  }
};
Point points[maxN];
lli totalArea, partialArea[maxN + 1];

lli evaluate(lli j, lli i)
{
  lli carolArea = partialArea[max(j, i)] - partialArea[min(i, j)] + points[max(j, i)].cross(points[min(i, j)]);
  lli carlaArea = totalArea - carolArea;
  if (carlaArea > carolArea) swap(carolArea, carlaArea);
  return(carolArea);
}

lli brute(lli lo, lli hi, lli base)
{
  lli ans = inf;
  for (lli k = lo; k <= hi; k ++)
    ans = min(ans, evaluate(k, base));
  return(ans);
}

lli ternarySearch(lli lo, lli hi, lli base)
{
  if (lo >= hi - 2) return(brute(lo, hi, base));
  lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
  lli elo = evaluate(midlo, base), ehi = evaluate(midhi, base);
  if (elo < ehi) return(ternarySearch(lo, midhi, base));
  if (ehi < elo) return(ternarySearch(midlo, hi, base));
  return(ternarySearch(midlo, midhi, base));
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%lld %lld", &points[i].x, &points[i].y);

  for (int i = 0; i < n; i ++)
  {
    totalArea += points[i].cross(points[(i + 1) % n]);
    partialArea[i + 1] = totalArea;
    // printf("%lld%c", partialArea[i + 1], i < n - 1 ? ' ' : '\n');
  }

  lli carolAns = 0;
  for (int i = 0; i < n; i ++)
  {
    lli minArea = min(i > 1 ? ternarySearch(0, i - 2, i) : inf, i < n - 2 ? ternarySearch(i + 2, n - 1, i) : inf);
    // for (int j = i + 2, a = 3; a < n; j ++, a ++)
    // {
    //   j %= n;
    //   lli carolArea = partialArea[max(j, i)] - partialArea[min(i, j)] + points[max(j, i)].cross(points[min(i, j)]);
    //   lli carlaArea = totalArea - carolArea;
    //   if (carlaArea > carolArea) swap(carolArea, carlaArea);
    //   minArea = min(minArea, carolArea);
    //   printf("%d (%lld, %lld) - %d (%lld %lld) = %lld, %lld\n", i, points[i].x, points[i].y, j, points[j].x, points[j].y, carolArea, carlaArea);
    // }
    if (minArea < inf) carolAns = max(carolAns, minArea);
  }
  printf("%lld %lld\n", carolAns, totalArea - carolAns);

  return(0);
}