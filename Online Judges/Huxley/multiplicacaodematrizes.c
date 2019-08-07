#include <stdio.h>

int main()
{
  int j, i, j2; scanf("%d %d %d", &j, &i, &j2);
  int matrizA[j][i], matrizB[i][j2], mult[j][j2], x, y, xM, yM;
  for (y = 0; y < j; y ++)
  {
    for (x = 0; x < j2; x ++)
    {
      mult[y][x] = 0;
    }
  }
  for (y = 0; y < j; y ++)
  {
    for (x = 0; x < i; x ++)
    {
      scanf("%d", &matrizA[y][x]);
    }
  }
  for (y = 0; y < i; y ++)
  {
    for (x = 0; x < j2; x ++)
    {
      scanf("%d", &matrizB[y][x]);
    }
  }
  for (y = 0; y < j; y ++)
  {
    for (xM = 0; xM < j2; xM ++)
    {
      for (x = 0; x < i; x ++)
      {
        mult[y][xM] += matrizA[y][x] * matrizB[x][xM];
      }
    }
  }
  for (y = 0; y < j; y ++)
  {
    for (x = 0; x < j2 - 1; x ++)
    {
      printf("%d ", mult[y][x]);
    }
    printf("%d\n", mult[y][x]);
  }
  return(0);
}
