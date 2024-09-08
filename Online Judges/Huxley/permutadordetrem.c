#include <stdio.h>

int main()
{
  int quanti, ordem, bubble, aux, passos = 0;
  scanf("%d", &quanti);
  int trem[quanti];
  for (ordem = 0; ordem < quanti; ordem ++)
  {
    scanf("%d", &trem[ordem]);
  }
  for (ordem = 0; ordem < quanti; ordem ++)
  {
    for (bubble = ordem; bubble < quanti; bubble ++)
    {
      if (trem[ordem] > trem[bubble])
      {
        aux = trem[ordem];
        trem[ordem] = trem[bubble];
        trem[bubble] = aux;
        passos ++;
      }
    }
  }
  printf("A melhor troca leva %d passos\n", passos);
  return(0);
}
