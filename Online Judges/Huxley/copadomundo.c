#include <stdio.h>

int main()
{
  int paises, jogos, empates;
  while (scanf("%d %d", &paises, &jogos) && !(paises == 0 && jogos == 0))
  {
    char pais[99]; int total = 0, pontos;
    while (paises > 0)
    {
      scanf("%s %d", pais, &pontos);
      total += pontos;
      paises --;
    }
    empates = (3 * jogos) - total;
    printf("%d\n", empates);
  }
  return(0);
}
