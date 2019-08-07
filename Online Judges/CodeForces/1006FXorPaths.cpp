#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
#define lli long long int
lli grid[20][20], n, m, middle, k;
unordered_map<lli, lli> bot[20][20], dp[20][20];

void build(int i, int j, lli prev)
{
  if (i >= n || j >= m) return;
  lli next = prev ^ grid[i][j];
  if (i + j == middle)
  {
    if (!bot[i][j].count(next)) bot[i][j][next] = 0;
    bot[i][j][next] ++;
    return;
  }
  build(i + 1, j, next);
  build(i, j + 1, next);
}

lli backPath(int i, int j, lli prev)
{
  if (i < 0 || j < 0) return(0);
  if (i + j == middle) return(bot[i][j].count(prev ^ k) ? bot[i][j][prev ^ k] : 0);
  lli next = prev ^ grid[i][j];
  if (!dp[i][j].count(prev))
    dp[i][j][prev] = backPath(i - 1, j, next) + backPath(i, j - 1, next);
  return(dp[i][j][prev]);
}

int main()
{
  scanf("%lld %lld %lld", &n, &m, &k);
  for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) scanf("%lld", &grid[i][j]);

  middle = (n + m) / 2 - 1;
  build(0, 0, 0);
  lli ans = backPath(n - 1, m - 1, 0);

  printf("%lld\n", ans);

  return(0);
}