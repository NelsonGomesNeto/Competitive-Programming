#include <stdio.h>
#include <math.h>

int main()
{
  float num[99], media = 0, varia = 0, desvio; int ler = 0, calc;
  while (scanf("%f", &num[ler]) != EOF)
  {
    media += num[ler];
    ler ++;
  }
  media /= ler;
  for (calc = 0; calc < ler; calc ++)
  {
    varia += (media - num[calc]) * (media - num[calc]);
  }
  varia /= ler;
  desvio = sqrt(varia);
  printf("%f\n", desvio);
  return(0);
}
