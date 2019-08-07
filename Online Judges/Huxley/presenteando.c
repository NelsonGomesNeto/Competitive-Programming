#include <stdio.h>

int altura[5], aux, repeat, ordem, me;

int orga()
{
  for (ordem = 0; ordem < 5; ordem ++)
  {
    for (me = 0; me < 5; me ++)
    {
      if (altura[ordem] < altura[me])
      {
        aux = altura[me];
        altura[me] = altura[ordem];
        altura[ordem] = aux;
      }
    }
  }
}

int main()
{
  scanf("%i %i %i %i %i", &altura[0], &altura[1], &altura[2], &altura[3], &altura[4]);
  orga();
  printf("%i\n%i\n%i\n", altura[0], altura[2], altura[4]);
  return(0);
}
