#include <stdio.h>

int main()
{
  int tam; scanf("%d", &tam);
  int i, atual = 1, altura = 0, tronco = 0;
  while (atual <= tam)
  {
    altura ++;
    if (altura % 3 == 1)
      tronco ++;

    if (atual < tam)
      for (i = 0; i < (tam - atual) / 2; i ++)
        printf("-");

    for (i = 0; i < atual; i ++)
      printf("*");

    if (atual < tam)
      for (i = 0; i < (tam - atual) / 2; i ++)
        printf("-");

    printf("\n");
    atual += 2;
  }
  atual = 1; altura = 0;
  while (altura < tronco)
  {
    altura ++;
    if (atual < tam)
      for (i = 0; i < (tam - atual) / 2; i ++)
        printf("-");

    for (i = 0; i < atual; i ++)
      printf("*");

    if (atual < tam)
      for (i = 0; i < (tam - atual) / 2; i ++)
        printf("-");

    printf("\n");
    atual += 2;
  }
  return(0);
}
