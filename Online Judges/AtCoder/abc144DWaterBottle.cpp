#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const ldouble pi = acos(-1), eps = 1e-10;
const ldouble pi2 = acos(-1) / 2;
ldouble a, b, x, v, h, needs;

ldouble radToDeg(ldouble angle)
{
  return (ldouble) 180 / pi * angle;
}

ldouble volume(ldouble angle)
{
  ldouble other = pi2 - angle;
  ldouble hh = b * tan(angle);
  if (hh <= a)
    return a * b * hh / 2;
  ldouble hhh = tan(other) * (hh - a);
  return a * a * hhh + a * (b - hhh) * a / 2;
}

ldouble binarySearch()
{
  ldouble lo = 0, hi = pi2;
  while ((hi - lo) >= eps)
  {
    ldouble mid = (lo + hi) / 2;
    if (volume(mid) <= x) lo = mid;
    else hi = mid;
  }
  return lo;
}

int main()
{
  scanf("%Lf %Lf %Lf", &a, &b, &x);
  h = x / (a * a);
  needs = b - h;
  printf("%.12Lf\n", 90 - radToDeg(binarySearch()));
  return 0;
}