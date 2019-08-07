#include <stdio.h>

int main()
{
  int pontos, total = 0, nvezes = 0;
  while (nvezes < 6)
  {
    scanf("%i", &pontos);
    total += pontos;
    nvezes ++;
  }
  if (total >= 100)
  {
    printf("Classificado\n");
  }
  else
  {
    printf("Eliminado\n");
  }
  return(0);
}
