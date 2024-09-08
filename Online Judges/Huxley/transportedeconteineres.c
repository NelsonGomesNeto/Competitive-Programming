#include <stdio.h>

int main()
{
  int A, B, C, Vcon, X, Y, Z, Vnav, total;
  scanf("%i %i %i\n%i %i %i", &A, &B, &C, &X, &Y, &Z);
  total = (Y / B) * (X / A) * (Z / C);
  //total = Vnav / Vcon;
  printf("%i\n", total);
  return(0);
}
