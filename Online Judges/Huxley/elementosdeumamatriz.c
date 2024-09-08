#include <stdio.h>

int main()
{
  int Y, X; scanf("%d %d", &Y, &X);
  int matriz[Y][X], j, i, menor = 0, maior = 0, dF = 0, dS = 0;
  for (j = 0; j < Y; j ++)
  {
    for (i = 0; i < X; i ++)
    {
      scanf("%d", &matriz[j][i]);
      if (i == j)
      {
        dF += matriz[j][i];
      }
      if (matriz[j][i] > 0)
      {
        maior ++;
      }
      else if (matriz[j][i] < 0)
      {
        menor ++;
      }
    }
  }
  for (j = 0, i = X - 1; j < Y; j ++, i --)
  {
    dS += matriz[j][i];
  }
  printf("Matriz formada:\n");
  for (j = 0; j < Y; j ++)
  {
    for (i = 0; i < X - 1; i ++)
    {
      printf("%d ", matriz[j][i]);
    }
    printf("%d\n", matriz[j][i]);
  }
  if (X == Y)
  {
    printf("A diagonal principal e secundaria tem valor(es) %d e %d respectivamente.\n", dF, dS);
  }
  else
  {
    printf("A diagonal principal e secundaria nao pode ser obtida.\n");
  }
  printf("A matriz possui %d numero(s) menor(es) que zero.\n", menor);
  printf("A matriz possui %d numero(s) maior(es) que zero.\n", maior);
  return(0);
}
