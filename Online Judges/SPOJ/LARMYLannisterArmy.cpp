#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 5e3 + 1; int n, k;
const int inf = INT_MAX;
int h[maxN], sum[maxN][maxN], cost[maxN][maxN];

int memo[maxN][maxN];
void solve(int i, int lo = 1, int hi = n, int optlo = 1, int opthi = n)
{
  if (lo > hi) return;

  int mid = (lo + hi) >> 1, optj = optlo;
  int &best = memo[i][mid] = inf, now;
  for (int j = optlo, end = min(mid, opthi); j <= end; j ++)
    if ((now = memo[i - 1][j] + cost[j + 1][mid]) <= best)
      best = now, optj = j;

  solve(i, lo, mid - 1, optlo, optj);
  solve(i, mid + 1, hi, optj, opthi);
}

int main()
{
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i ++)
    scanf("%d", &h[i]);

  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++)
      sum[i][j] = (j > i && h[i] > h[j]) + sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
  for (int i = 1; i <= n; i ++)
    for (int j = i + 1; j <= n; j ++)
      cost[i][j] = sum[j][j] - sum[i - 1][j] - sum[j][i - 1] + sum[i - 1][i - 1];

  if (k < n)
  {
    for (int i = 1; i <= n; i ++)
      memo[1][i] = cost[1][i];
    for (int i = 2; i <= k; i ++)
    {
      solve(i);
      if (memo[i][n] == 0)
        break;
    }
  }
  printf("%d\n", memo[k][n]);

  return(0);
}