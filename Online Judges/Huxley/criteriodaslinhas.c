#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
  int valido = 1;
  long double soma, alfa;
  for (i = 0; i < tam; i ++)
  {
    soma = 0;
    for (j = 0; j < tam; j ++)
    {
      if (i != j)
      {
        soma += matriz[i][j];
      }
    }
    alfa = soma / matriz[i][i];
    if (alfa >= 1)
    {
      valido = 0;
    }
  }
  if (valido == 1)
  {
    printf("SIM\n");
  }
  else
  {
    printf("NAO\n");
  }
  return(0);
}
