#include <stdio.h>

int main()
{
  int x, y, k, diag, matriz[4][4];
  while (scanf("%d", &k) & k != 0)
  {
    diag = 0;
    for (y = 0; y < 4; y ++)
    {
      for (x = 0; x < 4; x ++)
      {
        scanf("%d", &matriz[y][x]);
        if (x == diag && y == diag)
        {
          matriz[y][x] *= k;
        }
      }
      diag ++;
    }
    for (y = 0; y < 4; y ++)
    {
      for (x = 0; x < 3; x ++)
      {
        printf("%d ", matriz[x][y]);
      }
      printf("%d \n", matriz[x][y]);
    }
  }
  return(0);
}
