#include <stdio.h>

int ordem, bubble, aux, medida[3], H, L;

int orga()
{
  for (ordem = 0; ordem < 3; ordem ++)
  {
    for (bubble = 0; bubble < 3; bubble ++)
    {
      if (medida[ordem] < medida[bubble])
      {
        aux = medida[bubble];
        medida[bubble] = medida[ordem];
        medida[ordem] = aux;
      }
    }
  }
  }

int main()
{
  scanf("%i %i %i\n%i %i", &medida[0], &medida[1], &medida[2], &H, &L);
  orga();
  if ((medida[0] > H || medida[1] > L) && (medida[1] > H || medida[0] > L))
  {
    printf("N\n");
  }
  else
  {
    printf("S\n");
  }
  return(0);
}
