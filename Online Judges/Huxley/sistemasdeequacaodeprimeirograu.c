#include <stdio.h>

int main()
{
  float A, B, C, D, E, F, aux, y, x;
  scanf("%fx + %fy = %f", &A, &B, &C);
  scanf("%fx + %fy = %f", &D, &E, &F);
  aux = A;
  A *= (D * (-1)); B *= (D * (-1)); C *= (D * (-1));
  D *= aux; E *= aux; F *= aux;
  y = (C + F) / (B + E);
  x = (C - (B * y)) / A;
  printf("%.2f\n%.2f\n", x, y);
  return(0);
}
