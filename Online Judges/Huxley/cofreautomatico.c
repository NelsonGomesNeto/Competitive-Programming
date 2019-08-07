#include <stdio.h>

int main()
{
  int tam; scanf("%d", &tam);
  int cofre[tam], ler, change, aux[tam], posi;
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &cofre[ler]);
    aux[ler] = cofre[ler];
  }
  char oper; int vez;
  while (getchar() && scanf("%c %d", &oper, &vez) && oper != 'S')
  {
    if (oper == 'D')
    {
      for (change = 0; change < tam; change ++)
      {
        posi = tam - vez + change;
        posi = posi % tam;
        cofre[change] = aux[posi];
      }
    }
    else
    {
      for (change = 0; change < tam; change ++)
      {
        posi = change + vez;
        posi = posi % tam;
        cofre[change] = aux[posi];
      }
    }
    for (change = 0; change < tam; change ++)
    {
      aux[change] = cofre[change];
    }
    for (ler = 0; ler < tam; ler ++)
    {
      printf("%d ", cofre[ler]);
    }
    printf("\n");
  }
  return(0);
}
