#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5, inf = 1e6; int n;
int a[2][maxN];
int sum[2][maxN + 1];

int memo[2][maxN][2];
int solve(int i = 0, int j = 0, bool switched = false)
{
  if (j == n) return 0;
  if (memo[i][j][switched] == -1)
  {
    int ans = inf;
    if (!switched)
      ans = min(ans, 1 + solve(1 - i, j + 1, true));
    ans = min(ans, solve(i, j + 1, switched));
    ans += !a[i][j];
    memo[i][j][switched] = ans;
  }
  return memo[i][j][switched];
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < 2; i ++)
    for (int j = 0; j < n; j ++)
    {
      scanf("%d", &a[i][j]);
      sum[i][j + 1] = sum[i][j] + !a[i][j];
    }

  // memset(memo, -1, sizeof(memo));
  // int ans = min(solve(0), solve(1));
  int ans = min(sum[0][n], sum[1][n]);
  for (int i = 0; i < 2; i ++)
    for (int j = 0; j < n; j ++)
      ans = min(ans, sum[i][j + 1] + 1 + (sum[1 - i][n] - sum[1 - i][j + 1]));
  printf("%d\n", ans);

  return(0);
}