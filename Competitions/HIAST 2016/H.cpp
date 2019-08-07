#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    double l, w, vl, vr, s; scanf("%lf %lf %lf %lf %lf", &l, &w, &vl, &vr, &s);
    if (vl != vr)
    {
      double vf = max(vl, vr), vs = min(vl, vr);
      double r = vf * l / (vf - vs);
      double length = 2 * pi * r, runned = vf * 2 * pi * w * s;
      double done = runned / length;
      double angle = 2 * pi * done, mid = (r + (r - l)) / 2;
      printf("%.3lf %.3lf\n", (vr > vl ? 1 : -1) * (mid * cos(angle) - mid), mid * sin(angle));
    }
    else
      printf("0.000 %.3lf\n", vl * 2 * pi * w * s);
  }
  return(0);
}
