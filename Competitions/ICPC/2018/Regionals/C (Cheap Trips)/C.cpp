#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e4; int n;
struct Trip { int duration, cost; };
Trip trips[maxN];

double memo[maxN][121][7];

double solve(int i, int t, int done)
{
  // printf("%d %d %d\n", i, t, done);
  if (i == n) return(0);
  double &ans = memo[i][t >= 120 ? 120 : t][done];
  if (ans == -1)
  {
    ans = solve(i + 1, trips[i].duration, 1) + trips[i].cost;
    if (t < 120 && done == 1) ans = min(ans, trips[i].cost * 0.5 + solve(i + 1, t + trips[i].duration, done + 1));
    if (t < 120 && done > 1 && done <= 5) ans = min(ans, trips[i].cost * 0.25 + solve(i + 1, t + trips[i].duration, done + 1));
  }
  return(ans);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d %d", &trips[i].duration, &trips[i].cost);
  for (int i = 0; i < maxN; i ++) for (int j = 0; j <= 120; j ++) for (int k = 0; k < 7; k ++) memo[i][j][k] = -1;
  double ans = solve(0, 0, 0);
  printf("%.2lf\n", ans);
  return(0);
}