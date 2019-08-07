#include <bits/stdc++.h>
int n, m, k, dots = 0, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char mat[500][501];

void go(int i, int j)
{
  if (!dots || i < 0 || j < 0 || i >= n || j >= m || mat[i][j] != 'X') return;
  mat[i][j] = '.', dots --;
  for (int l = 0; l < 4; l ++) go(i + dy[l], j + dx[l]);
}

int main()
{
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0; i < n; i ++) scanf("\n%s", mat[i]);
  for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) if (mat[i][j] == '.') mat[i][j] = 'X', dots ++;
  dots -= k;

  for (int i = 0, done = 0; i < n && !done; i ++)
    for (int j = 0; j < m && !done; j ++)
      if (mat[i][j] == 'X')
        go(i, j);

  for (int i = 0; i < n; i ++)
    printf("%s\n", mat[i]);
  return(0);
}