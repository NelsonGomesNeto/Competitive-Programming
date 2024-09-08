#include <stdio.h>

int main()
{
  int testes; scanf("%d", &testes);
  while (testes > 0)
  {
    int hosp, menor, maior, max = 0, limit = 0; scanf("%d", &hosp);
    int tempo[2][hosp], ler;
    for (ler = 0; ler < hosp; ler ++)
    {
      scanf("%d", &tempo[0][ler]);
      if (ler == 0 || tempo[0][ler] < menor)
      {
        menor = tempo[0][ler];
      }
    }
    for (ler = 0; ler < hosp; ler ++)
    {
      scanf("%d", &tempo[1][ler]);
      if (ler == 0 || tempo[1][ler] > maior)
      {
        maior = tempo[1][ler];
      }
    }
    //printf("%d~~\n", maior);
    while (menor <= maior)
    {
      for (ler = 0; ler < hosp; ler ++)
      {
        if (tempo[0][ler] == menor)
        {
          max ++;
          tempo[0][ler] = -1;
        }
        if (tempo[1][ler] <= menor)
        {
          max --;
          tempo[1][ler] = 99999;
        }
        //printf("%d~~%d\n", menor, max);
      }
      if (max > limit)
      {
        limit = max;
      }
      menor ++;
    }
    printf("%d\n", limit);
    testes --;
  }
  return(0);
}
