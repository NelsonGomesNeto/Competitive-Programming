#include <bits/stdc++.h>
#define lli long long int
using namespace std;

struct Point
{
  double x, y;
  void read()
  {
    scanf("%lf %lf", &x, &y);
  }
  double dist(Point &p)
  {
    return(sqrt((x - p.x)*(x - p.x) + (y - p.y)*(y - p.y)));
  }
};

int main()
{
  Point a, b, c;
  a.read(); b.read(); c.read();

  double aDist = a.dist(c), bDist = b.dist(c);
  if (aDist < bDist)
    printf("A - %.2lf\n", aDist);
  else
    printf("B - %.2lf\n", bDist);

  return(0);
}