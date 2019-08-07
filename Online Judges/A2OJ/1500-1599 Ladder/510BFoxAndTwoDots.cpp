#include <bits/stdc++.h>
char game[50][51], color;
int n, m;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int si, sj;

int go(int i, int j, int prev)
{
  // printf("%d %d %c\n", i, j, color);
  if (i == si && j == sj && prev != -1) return(1);
  if (i < 0 || j < 0 || i >= n || j >= m || game[i][j] != color) return(0);

  char aux = game[i][j];
  game[i][j] = '0';
  int can = 0;
  for (int k = 0; k < 4 && !can; k ++)
    if ((k == -1 || (k + 2) % 4 != prev) && go(i + dy[k], j + dx[k], k))
      can = 1;
  game[i][j] = aux;

  return(can);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    scanf("\n%s", game[i]);

  int can = 0;
  for (int i = 0; i < n - 1; i ++)
  {
    for (int j = 0; j < m - 1; j ++)
    {
      color = game[i][j];
      si = i; sj = j;
      if (go(i, j, -1))
        can = 1;
    }
  }
  printf("%s\n", can ? "Yes" : "No");

  return(0);
}