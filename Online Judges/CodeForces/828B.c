#include <stdio.h>

int abso(int n)
{
  return(n < 0 ? n * -1 : n);
}

int max(int a, int b)
{
  return(a > b ? a : b);
}

int main()
{
  int y, x; scanf("%d %d", &y, &x);
  char mat[y][x]; int i, j;
  for (i = 0; i < y; i ++)
  {
    for (j = 0; j < x; j ++)
    {
      scanf("%c", &mat[i][j]);
      if (mat[i][j] < 'A' || mat[i][j] > 'Z')
        j --;
    }
  }

  int biggestSide = 1, blocks = 0, left = x, up = y, right = -1, down = -1;
  for (i = 0; i < y; i ++)
    for (j = 0; j < x; j ++)
      if (mat[i][j] == 'B')
      {
        if (j < left) left = j;
        if (j > right) right = j;
        if (i > down) down = i;
        if (i < up) up = i;
        blocks ++;
      }

  if (blocks > 1)
    biggestSide = down - up > right - left ? down - up + 1 : right - left + 1;

  int needed = (biggestSide * biggestSide) - blocks;

  if (biggestSide > y || biggestSide > x)
    printf("-1\n");
  else
    printf("%d\n", needed);

  return(0);
}
