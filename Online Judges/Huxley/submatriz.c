#include <stdio.h>
#include <stdlib.h>

int main()
{
  int tam; scanf("%d", &tam);
  long double matriz[tam][tam]; int i, j;
  for (i = 0; i < tam; i ++)
  {
    for (j = 0; j < tam; j ++)
    {
      scanf("%Lf", &matriz[i][j]);
    }
  }
  int y, x; scanf("%d %d", &y, &x);
  y --; x --;
  long double subMatriz[2][2];
  subMatriz[0][0] = matriz[y][y];
  subMatriz[0][1] = matriz[y][x];
  subMatriz[1][0] = matriz[x][y];
  subMatriz[1][1] = matriz[x][x];
  for (i = 0; i < 2; i ++)
  {
    for (j = 0; j < 1; j ++)
    {
      printf("%.2Lf ", subMatriz[i][j]);
    } printf("%.2Lf\n", subMatriz[i][j]);
  }
  return(0);
}
