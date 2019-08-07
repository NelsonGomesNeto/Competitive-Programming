#include <stdio.h>

int ordem, bubble; float altura[4], aux;

int orga()
{
  for (ordem = 0; ordem < 4; ordem ++)
  {
    for (bubble = 0; bubble < 4; bubble ++)
    {
      if (altura[ordem] < altura[bubble])
      {
        aux = altura[bubble];
        altura[bubble] = altura[ordem];
        altura[ordem] = aux;
      }
    }
  }
}

int main()
{
  for (ordem = 0; ordem < 4; ordem ++)
  {
    scanf("%f", &altura[ordem]);
  }
  orga();
  printf("%.2f\n%.2f\n%.2f\n%.2f\n", altura[0], altura[2], altura[3], altura[1]);
  return(0);
}
