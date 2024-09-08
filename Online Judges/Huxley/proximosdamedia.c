#include <stdio.h>
#include <stdlib.h>

double abso(double a, double b)
{
  return(a - b < 0 ? (a - b) * (-1) : (a - b));
}

int main()
{
  int numeros, i; scanf("%d", &numeros);
  double notas[numeros], media = 0;
  for (i = 0; i < numeros; i ++)
  {
    scanf("%lf", &notas[i]);
    media += notas[i];
  } media /= numeros;
  double dif; int closest;
  for (i = 0; i < numeros; i ++)
  {
    if (i == 0 || abso(media, notas[i]) < dif)
    {
      dif = abso(media, notas[i]);
      closest = i;
    }
  }
  printf("MEDIA: %.2lf\n", media);
  printf("MAIS PROXIMO: %.2lf\n", notas[closest]);
  printf("DIFERENCA: %.2lf\n", dif);
  return(0);
}
