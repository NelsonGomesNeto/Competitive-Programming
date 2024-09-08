#include <stdio.h>

int main()
{
  int x, y, rX, rY, i, j, viva, gera, run, live; scanf("%d %d %d %d", &y, &x, &viva, &gera);
  int Xcel, Ycel, matriz[x + 2][y + 2], aux[x + 2][y + 2];
  for (j = 0; j < y + 2; j ++)
  {
    for (i = 0; i < x + 2; i ++)
    {
      matriz[j][i] = 0;
      aux[j][i] = 0;
    }
  }
  for (run = 0; run < viva; run ++)
  {
    scanf("%d %d", &Xcel, &Ycel);
    matriz[Xcel + 1][Ycel + 1] = 1;
    aux[Xcel + 1][Ycel + 1] = 1;
  }
  for (run = 0; run < gera + 1; run ++)
  {
    for (j = 1; j < y + 1; j ++)
    {
      printf(" ");
      for (i = 1; i < x; i ++)
      {
        printf("%d ", matriz[j][i]);
        live = 0;
        for (rY = j - 1; rY < j + 2; rY ++)
        {
          for (rX = i - 1; rX < i + 2; rX ++)
          {
            if (matriz[rY][rX] == 1 && !(rY == j && rX == i))
            {
              live ++;
            }
          }
        }
        if (matriz[j][i] == 1 && live < 2)
        {
          aux[j][i] = 0;
        }
        else if (matriz[j][i] == 1 && live > 3)
        {
          aux[j][i] = 0;
        }
        else if (matriz[j][i] == 0 && live == 3)
        {
          aux[j][i] = 1;
        }
        else
        {
          aux[j][i] = matriz[j][i];
        }
      }
      printf("%d\n", matriz[j][i]);
      live = 0;
      for (rY = j - 1; rY < j + 2; rY ++)
      {
        for (rX = i - 1; rX < i + 2; rX ++)
        {
          if (matriz[rY][rX] == 1 && !(rY == j && rX == i))
          {
            live ++;
          }
        }
      }
      if (matriz[j][i] == 1 && live < 2)
      {
        aux[j][i] = 0;
      }
      else if (matriz[j][i] == 1 && live > 3)
      {
        aux[j][i] = 0;
      }
      else if (matriz[j][i] == 0 && live == 3)
      {
        aux[j][i] = 1;
      }
      else
      {
        aux[j][i] = matriz[j][i];
      }
    }
    printf("\n");
    for (j = 1; j < y + 1; j ++)
    {
      for (i = 1; i < x + 1; i ++)
      {
        matriz[j][i] = aux[j][i];
      }
    }
  }
  return(0);
}
