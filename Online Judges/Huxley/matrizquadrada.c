#include <stdio.h>
#include <math.h>
//FAÇA UMA METADE E DEPOIS A OUTRA!!!!
int main()
{
  int tam, j, i, meio = 1;
  while (scanf("%d", &tam) && tam != 0)
  {
    tam --; int matriz[tam][tam];
    if (tam >= 1)
    {
      for (j = 0; j <= tam / 2; j ++)
      {
        meio = 1;
        for (i = 0; i < tam; i ++)
        {
          if (i >= meio && j >= meio && i <= (tam / 2))// + j - 1)
          {
            meio ++;
          }
          if (i >= tam - j + 1)// && i > tam / 2)//meio - 1 && j >= meio && i >= tam / 2 && j > 0)
          {
            meio --;
          }
          matriz[i][j] = meio;
          printf("%d ", meio);
        }
        printf("1\n");
      }
    }
    meio = 1;
    if (tam % 2 != 0)
    {
      meio --;
    }
    if (tam >= 1)
    {
      for (j = ceil(tam / 2) - meio; j > 0; j --)
      {
        for (i = 0; i < tam; i ++)
        {
          printf("%d ", matriz[i][j]);
        }
        printf("1\n");
      }
      for (i = 0; i < tam; i ++)
      {
        printf("1 ");
      }
    }
    printf("1\n\n");
  }
  return(0);
}
