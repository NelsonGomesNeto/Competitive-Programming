#include <stdio.h>

void printarBugado(double num)
{
  if (num - (int) num == 0)
  {
    printf("%.1lf\n", num);
  }
  else
  {
    printf("%.2lf\n", num);
  }
}

int main()
{
  int dias; scanf("%d", &dias);
  double mes[dias], menor = -1, maior = -1, media = 0;
  int i, fechado = 0, min[dias], max[dias], j = 0, jM = 0;
  for (i = 0; i < dias; i ++)
  {
    scanf("%lf", &mes[i]);
    if ((menor == -1 || mes[i] < menor) && mes[i] > 0)
    {
      menor = mes[i];
    }
    if ((maior == -1 || mes[i] > maior) && mes[i] > 0)
    {
      maior = mes[i];
    }
    media += mes[i];
    if (mes[i] == 0)
    {
      fechado ++;
    }
  }
  for (i = 0; i < dias; i ++)
  {
    if (mes[i] == menor)
    {
      min[j] = i + 1; j ++;
    }
    if (mes[i] == maior)
    {
      max[jM] = i + 1; jM ++;
    }
  }
  printf("%d\n", dias - fechado);
  printarBugado(media / dias);
  printarBugado(media / (dias - fechado));
  printarBugado(maior);
  for (i = 0; i < jM; i ++)
  {
    printf("%d ", max[i]);
  } printf("\n");
  printarBugado(menor);
  for (i = 0; i < j; i ++)
  {
    printf("%d ", min[i]);
  } printf("\n");
  return(0);
}
