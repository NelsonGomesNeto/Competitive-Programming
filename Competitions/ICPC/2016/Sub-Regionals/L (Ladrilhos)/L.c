#include <stdio.h>

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
int counter;

void floodfill(int y, int x, int field[][x], int i, int j, int color)
{
  int k;
  for (k = 0; k < 4; k ++)
    if (i + dy[k] >= 0 && i + dy[k] < y
    &&  j + dx[k] >= 0 && j + dx[k] < x
    &&  color == field[i + dy[k]][j + dx[k]])
    {
      counter ++; field[i][j] -= 40001; field[i + dy[k]][j + dx[k]] -= 40001;
      floodfill(y, x, field, i + dy[k], j + dx[k], color);
    }

}

int min(int a, int b)
{
  return(a < b ? a : b);
}

int main()
{
  int y, x; scanf("%d %d", &y, &x);
  int campo[y][x], menor = y * x, i, j;
  for (i = 0; i < y; i ++)
    for (j = 0; j < x; j ++)
      scanf("%d", &campo[i][j]);

  for (i = 0; i < y; i ++)
    for (j = 0; j < x; j ++)
      if (campo[i][j] >= 0)
      {
        counter = 1;
        floodfill(y, x, campo, i, j, campo[i][j]);
        menor = min(menor, counter);
      }

  printf("%d\n", menor);
  return(0);
}
