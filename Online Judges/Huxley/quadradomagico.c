#include <stdio.h>

int main()
{
  int tam, i, j; scanf("%d", &tam);
  int matriz[tam][tam], soma[(tam * 2) + 10], diag = 0;
  for (i = 0; i < 2 * tam + 4; i ++)
  {
    soma[i] = 0;
  }
  for (j = 0; j < tam; j ++)
  {
    for (i = 0; i < tam; i ++)
    {
      scanf("%d", &matriz[i][j]);
    }
    soma[0] += matriz[0][j];
  }
  //printf("Comp: %d\n", soma[0]);
  i = 0;
  for (j = 0; j < tam; j ++)
  {
    for (i = 0; i < tam; i ++)
    {
      soma[j + 1] += matriz[i][j];
      if (i == j)
      {
        soma[1 + (2 * tam)] += matriz[i][j];
      }
    }
    //printf("Linha: %d\n", soma[j + 1]);
  }
  //printf("Diag: %d\n", soma[1 + (2 * tam)]);
  j = 0;
  for (i = 0; i < tam; i ++)
  {
    for (j = 0; j < tam; j ++)
    {
      soma[i + 1 + tam] += matriz[i][j];
    }
    //printf("Linha: %d\n", soma[i + 1 + tam]);
    soma[1 + (2 * tam) + 1] += matriz[i][(j - 1) - i];
  }
  //printf("Diag: %d\n", soma[1 + (2 * tam) + 1]);
  for (i = 1; i <= 2 * tam + 2; i ++)
  {
    if (soma[0] != soma[i])
    {
      printf("-1\n");
      return(0);
    }
  }
  printf("%d\n", soma[0]);
  return(0);
}
