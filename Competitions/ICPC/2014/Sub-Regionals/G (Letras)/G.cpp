#include <bits/stdc++.h>
using namespace std;

const int maxN = 100, inf = 1e6; int n;
int mat[maxN][maxN]; bool can[maxN][maxN];

int di[4] = {1, 0, -1, 0}, dj[4] = {0, 1, 0, -1};
int bfs()
{
  if (!can[0][0]) return(inf);
  queue<pair<int, pair<int, int>>> q; q.push({1, {0, 0}});
  while (!q.empty())
  {
    int d = q.front().first, i = q.front().second.first, j = q.front().second.second; q.pop();
    if (i == n - 1 && j == n - 1) return(d);
    can[i][j] = false;
    for (int k = 0; k < 4; k ++)
    {
      int ni = i + di[k], nj = j + dj[k];
      if (ni < 0 || nj < 0 || ni >= n || nj >= n || !can[ni][nj]) continue;
      q.push({d + 1, {ni, nj}});
    }
  }
  return(inf);
}

int main()
{
  scanf("%d", &n);
  char ss[n + 1];
  for (int i = 0; i < n; i ++)
  {
    scanf(" %s", ss);
    for (int j = 0; j < n; j ++)
      if (ss[j] >= 'a' && ss[j] <= 'z')
        mat[i][j] = ss[j] - 'a' + 10;
      else
        mat[i][j] = ss[j] - 'A';
  }

  int ans = inf;
  for (int bitmask = 0, end = 1 << 10; bitmask < end; bitmask ++)
  {
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        if (mat[i][j] < 10)
          can[i][j] = bitmask & (1 << mat[i][j]);
        else
          can[i][j] = !(bitmask & (1 << (mat[i][j] - 10)));
    ans = min(ans, bfs());
  }

  printf("%d\n", ans >= inf ? -1 : ans);

  return(0);
}