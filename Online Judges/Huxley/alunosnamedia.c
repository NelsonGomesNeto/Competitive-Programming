#include <stdio.h>

int main()
{
  int nvezes, nvezesbackup;
  double notas[20000], media = 0;
  int notasmaior = 0, notasmenor = 0;
  scanf("%i", &nvezes);
  nvezesbackup = nvezes;
  while (nvezes > 0)
  {
    scanf("%lf", &notas[nvezes]);
    media += (notas[nvezes]/nvezesbackup);
    nvezes --;
  }
  nvezes = nvezesbackup;
  while (nvezes > 0)
  {
    if ((notas[nvezes] / media) > 1.1)
    {
      notasmaior += 1;
    }
    else if ((notas[nvezes] / media) < 0.9)
    {
      notasmenor += 1;
    }
    nvezes --;
  }
  printf("%.2lf\n%i\n%i\n", media, notasmaior, notasmenor);
  return(0);
}
