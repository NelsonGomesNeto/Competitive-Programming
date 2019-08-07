#include <stdio.h>

int main()
{
  int tam; scanf("%d", &tam);
  int num[tam], ler, soma = 0, aux = 0, tostop = 0, posi = 0, ativ = 0;
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &num[ler]);
  }
  if (tam > 1)
  {
    while (tostop == 0)
    {
      //printf("%d~~%d\n", soma, aux);
      if (posi >= tam)
      {
        posi %= tam;
      }
      if (soma + num[posi] >= soma)
      {
        soma += num[posi];
        ativ ++;
      }
      else
      {
        if (aux < soma)
        {
          aux = soma;
        }
        else if (aux == soma)
        {
          tostop = 1;
        }
        soma = 0;
      }
      posi ++;
    }
    int ordem, bubble, auxC;
    for (ordem = 0; ordem < tam; ordem ++)
    {
      for (bubble = ordem; bubble < tam; bubble ++)
      {
        if (num[ordem] > num[bubble])
        {
          auxC = num[ordem];
          num[ordem] = num[bubble];
          num[bubble] = auxC;
        }
      }
    }
    if (aux == 0)
    {
      printf("%d\n", num[tam - 1]);
    }
    else
    {
      printf("%d\n", aux);
    }
  }
  else
  {
    printf("%d\n", num[tam - 1]);
  }
  return(0);
}
