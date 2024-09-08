#include <stdio.h>
#include <math.h>

int main()
{
  int ate, run; scanf("%d", &ate);
  unsigned long long int prev = 1, prev2 = 0, atual = 0, aux;
  for (run = 0; run < ate; run ++)
  {
    aux = atual;
    atual = prev + prev2;
    prev2 = prev;
    prev = aux;
    printf("%Ld\n", atual);
  }
  return(0);
}
