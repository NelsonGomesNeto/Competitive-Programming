#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 80, inf = 1e7, mid = 80*80; int n, m;
int a[2][maxN][maxN];

// int memo[maxN][maxN][2*maxN*maxN + 1];
bitset<80*(80 + 80 + 1)> memo[maxN][maxN];
// int solve(int i = 0, int j = 0, int d = 0)
// {
//   if (i == n - 1 && j == m - 1) return min(abs(d + a[0][i][j] - a[1][i][j]), abs(d + a[1][i][j] - a[0][i][j]));
//   if (memo[i][j][d] != -1) return memo[i][j][d];
//   int ans = inf;
//   if (i + 1 < n)
//   {
//     ans = min(ans, solve(i + 1, j, abs(d + a[0][i][j] - a[1][i][j])));
//     ans = min(ans, solve(i + 1, j, abs(d + a[1][i][j] - a[0][i][j])));
//   }
//   if (j + 1 < m)
//   {
//     ans = min(ans, solve(i, j + 1, abs(d + a[0][i][j] - a[1][i][j])));
//     ans = min(ans, solve(i, j + 1, abs(d + a[1][i][j] - a[0][i][j])));
//   }
//   return memo[i][j][d] = ans;
// }
int solve()
{
  for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) memo[i][j] = 0;
  memo[0][0][mid + abs(a[0][0][0] - a[1][0][0])] = memo[0][0][mid - abs(a[0][0][0] - a[1][0][0])] = true;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
    {
      if (i)
        memo[i][j] |= (memo[i - 1][j] >> abs(a[0][i][j] - a[1][i][j])) | (memo[i - 1][j] << abs(a[0][i][j] - a[1][i][j]));
      if (j)
        memo[i][j] |= (memo[i][j - 1] >> abs(a[0][i][j] - a[1][i][j])) | (memo[i][j - 1] << abs(a[0][i][j] - a[1][i][j]));
    }
  for (int i = 0; ; i ++)
    if (memo[n - 1][m - 1][mid + i] || memo[n - 1][m - 1][mid - i])
      return i;
  return inf;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < 2; i ++)
      for (int j = 0; j < n; j ++)
        for (int k = 0; k < m; k ++)
          scanf("%d", &a[i][j][k]);
    // memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}