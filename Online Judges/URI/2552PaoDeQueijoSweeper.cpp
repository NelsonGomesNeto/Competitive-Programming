#include <bits/stdc++.h>
int game[100][100 + 1], dy[4] = {0, 0, 1, -1}, dx[4] = {1, -1, 0, 0}, n, m;

int valid(int i, int n)
{
  return(!(i < 0 || i >= n));
}

int around(int i, int j)
{
  int a = 0;
  for (int k = 0; k < 4; k ++)
    if (valid(i + dy[k], n) && valid(j + dx[k], m) && game[i + dy[k]][j + dx[k]] == 9)
      a ++;
  return(a);
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
      {
        scanf("%d", &game[i][j]);
        game[i][j] *= 9;
      }

    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        if (game[i][j] != 9)
          game[i][j] = around(i, j);

    for (int i = 0; i < n; i ++)
    {
      for (int j = 0; j < m; j ++)
        printf("%d", game[i][j]);
      printf("\n");
    }
  }
  return(0);
}