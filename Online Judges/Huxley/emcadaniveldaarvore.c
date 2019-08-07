#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
  int nos; scanf("%d", &nos);
  int a[nos][3], directions[nos * 3];
  int i, j, k = 1;
  directions[0] = 0;
  for (i = 0; i < nos; i ++)
  {
    for (j = 0; j < 3; j ++)
    {
      scanf("%d", &a[i][j]);
      if (j > 0 && a[i][j] != -1)
      {
        directions[k] = a[i][j];
        k ++;
      }
    }
  }
  int quanti = 1, aux = 0, menor = 9999999, menorAux = 9999999, maior = -9999999, maiorAux = -9999999, level = 1;
  for (i = 0; i < nos; i ++)
  {
    //printf("%d\n", a[y][0]);
    if (a[directions[i]][0] < menorAux)
    {
      menorAux = a[directions[i]][0];
    }
    if (a[directions[i]][0] > maiorAux)
    {
      maiorAux = a[directions[i]][0];
    }
    if (a[directions[i]][1] != -1)
    {
      aux += 1;
    }
    if (a[directions[i]][2] != -1)
    {
      aux += 1;
    }
    quanti -= 1;
    if (quanti == 0)
    {
      printf("Nivel %d: Maior = %d, Menor = %d\n", level, maiorAux, menorAux);

      menorAux = menor;
      maiorAux = maior;
      level += 1;
      quanti = aux;
      aux = 0;
    }
  }
  return(0);
}
