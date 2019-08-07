#include <stdio.h>

int main()
{
  int ano, intervalo, repeat;
  scanf("%d\n%d", &ano, &intervalo);
  for (repeat = 0; repeat < 2; repeat ++)
  {
    ano += intervalo;
    printf("%d ", ano);
  }
  printf("%d\n", ano + intervalo);
}
