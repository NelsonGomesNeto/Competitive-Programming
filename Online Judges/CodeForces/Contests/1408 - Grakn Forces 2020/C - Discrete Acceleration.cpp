#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxL = 1e9; int n; lli l;
const double eps = 1e-7;
lli a[maxN + 2];

double loPos(double t)
{
  lli pos = 0, speed = 1; int i = 1; double curr = 0;
  while (curr < t && i <= n + 1)
  {
    lli dist = a[i] - pos;
    double wt = (double)dist / speed;
    if (curr + wt > t)
      return pos + speed * (t - curr);
    curr += wt;
    pos = a[i++];
    speed++;
  }
  return pos;
}
double hiPos(double t)
{
  lli pos = l, speed = 1; int i = n; double curr = 0;
  while (curr < t && i >= 0)
  {
    lli dist = pos - a[i];
    double wt = (double)dist / speed;
    if (curr + wt > t)
      return pos - speed * (t - curr);
    curr += wt;
    pos = a[i--];
    speed++;
  }
  return pos;
}
bool can(double t)
{
  DEBUG printf("%lf | %lf %lf\n", t, loPos(t), hiPos(t));
  return loPos(t) >= hiPos(t);
}
double binarySearch()
{
  double lo = 0, hi = maxL;
  while (lo <= hi - eps)
  {
    double mid = (lo + hi) / 2;
    if (can(mid)) hi = mid;
    else lo = mid;
  }
  return hi;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %lld", &n, &l);
      for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
      a[0] = 0, a[n + 1] = l;

      double ans = binarySearch();
      printf("%.15lf\n", ans);
    }
  return 0;
}
