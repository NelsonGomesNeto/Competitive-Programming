#include <bits/stdc++.h>
using namespace std;
#define lli long long int
typedef struct point
{
  lli x, y;
} point;

/*
triangle area given points a, b and c
1/2 * det({a.x, b.x, c.x},
          {a.y, b.y, c.y},
          {  1,   1,   1})
*/

lli triangleArea(point a, point b, point c)
{
  return((a.x * b.y + b.x * c.y + c.x * a.y) - (c.x * b.y + b.x * a.y + a.x * c.y));
}

int main()
{
  int n; scanf("%d", &n);
  point a[n];
  for (int i = 0; i < n; i ++) scanf("%lld %lld", &a[i].x, &a[i].y);

  lli minArea = LLONG_MAX;
  for (int i = 0; i < n; i ++)
    minArea = min(minArea, triangleArea(a[i], a[(i + 1) % n], a[(i + 2) % n]));
  printf("%lld\n", minArea);
}