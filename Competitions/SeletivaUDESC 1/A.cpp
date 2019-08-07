#include <bits/stdc++.h>
char field[100][103];

int main()
{
  int m, n, t = 0;
  while (scanf("%d %d", &m, &n) != EOF)
  {
    if (t ++) printf("\n");
    memset(field, '.', sizeof(field));
    for (int i = 0; i < m + 2; i ++)
    {
      field[0][i] = '*';
      field[i][0] = '*';
      field[m-1+2][i] = '*';
      field[i][m-1+2] = '*';
      field[i][m + 2] = '\0';
    }

    int s, x, y;
    while (n --)
    {
      scanf("%d %d %d", &s, &x, &y); y += m - 1;
      printf("%d %d\n", x, y);
      if (s == 0)
      {
        if (x >= 0 && x <= m && y >= 0 && y < m)
        {
          field[y + 1][x + 1 - 1] = '_';
          if (x + 1 < m) field[y + 1][x + 2 - 1] = 'o';
          if (x + 2 <= m) field[y + 1][x + 3 - 1] = '_';
        }
      }
      else
      {
        if (x >= 0 && x <= m && y >= 0 && y < m)
        {
          field[y + 1][x + 1 - 1] = '_';
          if (x + 1 < m) field[y + 1][x + 2 - 1] = '|';
          if (x + 2 <= m) field[y + 1][x + 3 - 1] = '_';
        }
        for (int j = 1; j <= s && (y - j) >= 0 && (y - j) < m; j ++)
        {
          field[y + 1 - j][x + 1 - 1] = '/';
          if (x + 1 <= m) field[y + 1 - j][x + 2 - 1] = '|';
          if (x + 2 <= m) field[y + 1 - j][x + 3 - 1] = '\\';
        }
        if (x >= 0 && x + 1 <= m) field[y + 1 - s][x + 2 - 1] = '^';
      }
    }

    for (int i = 0; i < m + 2; i ++)
      printf("%s\n", field[i]);
  }

  return(0);
}