#include <stdio.h>

int grid;
int dirX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dirY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

void floodFill(char f[][grid], int y, int x)
{
  int i;
  for (i = 0; i < 8; i ++)
  {
    if (x + dirX[i] < grid && x + dirX[i] >= 0
    &&  y + dirY[i] < grid && y + dirY[i] >= 0
    &&  f[y + dirY[i]][x + dirX[i]] == '1')
    {
      f[y + dirY[i]][x + dirX[i]] = '0';
      floodFill(f, y + dirY[i], x + dirX[i]);
    }
  }
}

int main()
{
  int run = 1;
  while (scanf("%d", &grid) != EOF)
  {
    char foto[grid][grid]; int i, j;
    for (i = 0; i < grid; i ++)
    {
      for (j = 0; j < grid; j ++)
      {
        scanf("%c", &foto[i][j]);
        if (!(foto[i][j] == '0' || foto[i][j] == '1'))
          j --;
      }
    }
    int warEagles = 0;
    for (i = 0; i < grid; i ++)
    {
      for (j = 0; j < grid; j ++)
      {
        if (foto[i][j] == '1')
        {
          foto[i][j] = '0';
          floodFill(foto, i, j);
          warEagles ++;
        }
      }
    }
    printf("Image number %d contains %d war eagles.\n", run, warEagles);
    run ++;
  }
  return(0);
}
