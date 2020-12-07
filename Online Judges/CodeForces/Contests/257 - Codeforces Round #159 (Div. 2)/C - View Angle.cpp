#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

long double pi = acos(-1);

long double rad2deg(long double angle)
{
  return(180*angle/pi);
}

long double keepPositive(long double angle)
{
  return(angle < 0 ? angle + 2*pi : angle);
}

int main()
{
  int n; scanf("%d", &n);
  long double angle[n], x, y;
  for (int i = 0; i < n; i ++)
  {
    scanf("%Lf %Lf", &x, &y);
    angle[i] = acos(x/sqrt(x*x + y*y));
    if (y < 0) angle[i] = keepPositive(-angle[i]);
    DEBUG printf("%Lf\n", rad2deg(angle[i]));
  }
  sort(angle, angle+n);

  long double best = 2*pi;

  for (int i = 0, j = 1; i < n; i ++, j ++)
  {
    j %= n;
    if (keepPositive(angle[i] - angle[j]) > 0)
      best = min(best, keepPositive(angle[i] - angle[j]));
  }

  printf("%.10Lf\n", rad2deg(best == 2*pi ? 0 : best));

  return(0);
}
// theta = acos(<u, v> / (||u|| * ||v||))
/*
pi - 180
y  -  x
x*pi = 180*y
x = 180*y/pi
*/