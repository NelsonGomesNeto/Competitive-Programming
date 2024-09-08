#include <stdio.h>

void swap(int *a, int *b)
{
  int aux;
  if (*a < *b)
  {
    aux = *a;
    *a = *b;
    *b = aux;
  }
}

int main()
{
  int Y, X, retangulos;
  while (scanf("%d %d %d", &X, &Y, &retangulos) && !(Y == 0 && X == 0 && retangulos == 0))
  {
    int j, i, matriz[Y][X], Xi, Yi, Xf, Yf, empty = 0;
    for (j = 0; j < Y; j ++)
    {
      for (i = 0; i < X; i ++)
      {
        matriz[j][i] = 0;
      }
    }
    while (retangulos > 0)
    {
      scanf("%d %d %d %d", &Xi, &Yi, &Xf, &Yf);
      swap(&Xf, &Xi); swap(&Yf, &Yi);
      //printf("%d %d %d %d\n", Xi, Yi, Xf, Yf);
      for (j = Yi - 1; j < Yf; j ++)
      {
        for (i = Xi - 1; i < Xf; i ++)
        {
          matriz[j][i] = 1;
        }
      }
      retangulos --;
    }
    for (j = 0; j < Y; j ++)
    {
      for (i = 0; i < X; i ++)
      {
        if (matriz[j][i] == 0)
        {
          empty ++;
        }
      }
    }
    if (empty == 0)
    {
      printf("There is no empty spots.\n");
    }
    else if (empty == 1)
    {
      printf("There is one empty spot.\n");
    }
    else
    {
      printf("There are %d empty spots.\n", empty);
    }
  }
  return(0);
}
