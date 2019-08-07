#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e3; int n, t;
double segments[maxN][2], minimum = 1e18;

double eval(double c)
{
  double now = 0;
  for (int i = 0; i < n; i ++)
    now += segments[i][0] / (segments[i][1] + c);
  return(now);
}
double binarySearch(double lo = -minimum, double hi = 1e9)
{
  if (lo >= hi - 1e-10) return(lo);
  double mid = (lo + hi) / 2;
  if (eval(mid) <= t)
  {
    return(binarySearch(lo, mid));
    // if (mid >= 0)
    // else return(binarySearch(mid, hi));
  }
  else
  {
    return(binarySearch(mid, hi));
    // if (mid >= 0)
    // else return(binarySearch(lo, mid));
  }
}

int main()
{
  scanf("%d %d", &n, &t);
  for (int i = 0; i < n; i ++)
  {
    scanf("%lf %lf", &segments[i][0], &segments[i][1]);
    minimum = min(minimum, segments[i][1]);
  }

  double ans = binarySearch();
  printf("%.10lf\n", ans);

  return(0);
}