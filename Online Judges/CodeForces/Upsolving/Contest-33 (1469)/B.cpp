#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n, m;
int r[maxN], b[maxN];

int memo[maxN + 1][maxN + 1];
int solve(int i = 0, int j = 0, int sum = 0)
{
  if (i == n && j == m) return sum;
  int &ans = memo[i][j];
  if (ans != -1) return ans;

  ans = 0;
  if (i < n) ans = max({ans, solve(i + 1, j, sum + r[i]), sum + r[i]});
  if (j < m) ans = max({ans, solve(i, j + 1, sum + b[j]), sum + b[j]});
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d", &r[i]);

    scanf("%d", &m);
    for (int i = 0; i < m; i++)
      scanf("%d", &b[i]);

    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= m; j++)
        memo[i][j] = -1;
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}
