#include <stdio.h>

int main()
{
  int tam, sorte, ler, ordem, bubble, aux;
  scanf("%d %d", &tam, &sorte);
  int num[tam], vale[5], posi = 0;
  for (ler = 0; ler < 5; ler ++)
  {
    vale[ler] = -1;
  }
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &num[ler]);
  }
  for (ordem = 0; ordem < tam; ordem ++)
  {
    for (bubble = ordem; bubble < tam; bubble ++)
    {
      if (num[ordem] < num[bubble])
      {
        aux = num[ordem];
        num[ordem] = num[bubble];
        num[bubble] = aux;
      }
    }
  }
  for (ler = 0; ler < tam; ler ++)
  {
    if (num[ler] % 10 == sorte)
    {
      vale[posi] = num[ler];
      posi ++;
      if (posi > 4)
      {
        ler = tam;
      }
    }
  }
  for (ordem = 0; ordem < 5; ordem ++)
  {
    for (bubble = ordem; bubble < 5; bubble ++)
    {
      if (vale[ordem] > vale[bubble])
      {
        aux = vale[ordem];
        vale[ordem] = vale[bubble];
        vale[bubble] = aux;
      }
    }
  }
  for (ler = 0; ler < 5; ler ++)
  {
    printf("%d\n", vale[ler]);
  }
  return(0);
}
