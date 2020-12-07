#include <stdio.h>

int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {0, -1, 1, -1, 1, -1, 1, 0};

int tryflood(char t[][10], int i, int j)
{
  int k, y, x;
  for (k = 0; k < 8; k ++)
  {
    y = i - dy[k]; x = j - dx[k];
    int m = 0, win = 0, white = 0;
    do
    {
      y += dy[k]; x += dx[k];

      if (t[y][x] == '.')
        white ++;
      if (t[y][x] == 'X')
        win ++;

      m ++;
    } while (m < 5 && y + dy[k] >= 0 && y + dy[k] < 10 && x + dx[k] >= 0 && x + dx[k] < 10);

    if (win == 4 && white == 1)
      return(1);
  }
  return(0);
}

int main()
{
  char table[10][10];
  int i, j;
  for (i = 0; i < 10; i ++)
  {
    for (j = 0; j < 10; j ++)
      scanf("%c", &table[i][j]);
    getchar();
  }

  for (i = 0; i < 10; i ++)
    for (j = 0; j < 10; j ++)
      if (table[i][j] == 'X')
        if (tryflood(table, i, j))
        {
          printf("YES\n");
          return(0);
        }

  printf("NO\n");
  return(0);
}
