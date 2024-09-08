#include <stdio.h>

int main()
{
  int A, B, C, D, diferenca;
  scanf("%i %i %i %i", &A, &B, &C, &D);
  diferenca = (A * B) - (C * D);
  printf("DIFERENCA = %i\n", diferenca);
  return(0);
}
