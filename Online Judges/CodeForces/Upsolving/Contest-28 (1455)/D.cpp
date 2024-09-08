#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e2; int n, x;
int a[maxN];

const int inf = maxN + 1;
int memo[maxN][maxN + 1][maxN + 1];
int solve(int i = 0, int c = x, int prv = 0)
{
  if (i == n) return 0;
  int &ans = memo[i][c][prv];
  if (ans != -1) return ans;

  ans = inf;
  if (prv <= a[i]) ans = min(ans, solve(i + 1, c, a[i]));
  if (a[i] > c && prv <= c) ans = min(ans, solve(i + 1, a[i], c) + 1);

  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    for (int i = 0; i < n; i++)
      for (int j = 0; j <= maxN; j++)
        for (int k = 0; k <= maxN; k++)
          memo[i][j][k] = -1;
    int ans = solve();
    if (ans >= inf) ans = -1;
    printf("%d\n", ans);
  }
  return 0;
}
