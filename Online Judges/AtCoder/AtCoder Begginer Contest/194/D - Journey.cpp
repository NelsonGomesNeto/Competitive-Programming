#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n;
/*
  a*(b + b^2 + ...)
*/

const int maxN = 1e5;
const double eps = 1e-18;
double memo[maxN];
double solve(int i = 0)
{
  if (i == n - 1)
    return 0;

  double &ans = memo[i];
  if (ans != -1)
    return ans;

  double before = (double)(i + 1) / n;
  double after = 1 - before;

  ans = 1 + after*solve(i + 1);
  double sumBefore = before, b = before;
  while (before > eps)
  {
    before *= b;
    sumBefore += before;
  }
  ans += sumBefore * ans;

  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      memo[i] = -1;

    double ans = solve();
    printf("%.15lf\n", ans);
  }
  return 0;
}
