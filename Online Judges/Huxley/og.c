#include <stdio.h>

int main()
{
  int L, R, filhos;
  while (scanf("%i %i", &L, &R) && !(L == 0 && R == 0))
  {
    filhos  = L + R;
    printf("%i\n", filhos);
  }
  return(0);
}
