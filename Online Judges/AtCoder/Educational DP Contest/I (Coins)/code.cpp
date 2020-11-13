#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3; int n;
double p[maxN];

double memo[maxN][maxN];
double solve(int h = 0, int t = 0)
{
  if (h + t == n) return h > t;
  double &ans = memo[h][t];
  if (ans != -1) return ans;

  ans = p[h + t]*solve(h + 1, t) + (1 - p[h + t])*solve(h, t + 1);
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lf", &p[i]);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        memo[i][j] = -1;
    double ans = solve();
    printf("%.15lf\n", ans);
  }
  return 0;
}