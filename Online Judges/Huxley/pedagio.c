#include <stdio.h>

int main()
{
  int L, D, K, P, custo, pedagios;
  scanf("%i %i\n%i %i", &L, &D, &K, &P);
  pedagios = L / D;
  custo = (K * L) + (P * pedagios);
  printf("%i\n", custo);
  return(0);
}
