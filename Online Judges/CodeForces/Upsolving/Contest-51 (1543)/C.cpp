#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const double eps = 1e-12;
double c, m, p, v;

double solve(double cc = c, double mm = m, double pp = p)
{
  // if (cc < 0.05 || mm < 0.05) return 1;
  if (abs(pp - 1) <= eps) return 1;

  double ans = pp;

  if (cc > eps)
  {
    if (cc <= v || abs(cc - v) <= eps)
    {
      if (mm <= eps)
        ans += cc * (1 + solve(0, mm, pp + cc));
      else
        ans += cc * (1 + solve(0, mm + cc / 2, pp + cc / 2));
    }
    else
    {
      if (mm <= eps)
        ans += cc * (1 + solve(cc - v, mm, pp + v));
      else
        ans += cc * (1 + solve(cc - v, mm + v / 2, pp + v / 2));
    }
  }

  if (mm > eps)
  {
    if (mm <= v || abs(mm - v) <= eps)
    {
      if (cc <= eps)
        ans += mm * (1 + solve(cc, 0, pp + mm));
      else
        ans += mm * (1 + solve(cc + mm / 2, 0, pp + mm / 2));
    }
    else
    {
      if (cc <= eps)
        ans += mm * (1 + solve(cc, mm - v, pp + v));
      else
        ans += mm * (1 + solve(cc + v / 2, mm - v, pp + v / 2));
    }
  }

  // ans += 1;

  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lf %lf %lf %lf", &c, &m, &p, &v);

    double ans = solve();
    printf("%.15lf\n", ans);
  }
  return 0;
}
