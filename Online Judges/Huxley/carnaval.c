#include <stdio.h>

int ordem, bubble; float notas[5], soma, aux;

float orga()
{
  for (ordem = 0; ordem < 5; ordem ++)
  {
    for (bubble = 0; bubble < 5; bubble ++)
    {
      if (notas[ordem] < notas[bubble])
      {
        aux = notas[bubble];
        notas[bubble] = notas[ordem];
        notas[ordem] = aux;
      }
    }
  }
}

int main()
{
  scanf("%f %f %f %f %f", &notas[0], &notas[1], &notas[2], &notas[3], &notas[4]);
  orga();
  soma = notas[1] + notas[2] + notas[3];
  printf("%.1f\n", soma);
}
