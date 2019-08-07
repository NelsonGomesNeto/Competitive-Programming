#include <bits/stdc++.h>
char grid[50][51], copy[50][51];
int n, m, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

void go(int i, int j, int prevDir, int done)
{
  if (done > 1 || i < 0 || j < 0 || i >= n || j >= m || grid[i][j] == 'W') return;
  grid[i][j] = copy[i][j] = 'W';
  for (int k = 0; k < 4; k ++)
    go(i + dy[k], j + dx[k], k, prevDir != k ? done + 1 : done);
  grid[i][j] = 'B';
}

int verify()
{
  for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) if (copy[i][j] == 'B') return(0);
  return(1);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++) scanf("\n%s", grid[i]);
  memcpy(copy, grid, sizeof(grid));
  int possible = 1;
  for (int i = 0; i < n && possible; i ++)
    for (int j = 0; j < m && possible; j ++)
      if (grid[i][j] == 'B')
      {
        go(i, j, -1, -1);
        if (!verify()) possible = 0;
        memcpy(copy, grid, sizeof(grid));
      }

  printf("%s\n", possible ? "YES" : "NO");
  return(0);
}
