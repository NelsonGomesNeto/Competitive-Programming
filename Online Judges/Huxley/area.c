#include <stdio.h>

int main()
{
  double A, B, C, Pi = 3.14159, tri, cir, tra, qua, ret;
  scanf("%lf %lf %lf", &A, &B, &C);
  tri = (A * C) / 2;
  cir = Pi * C * C;
  tra = ((A + B) * C) / 2;
  qua = B * B;
  ret = A * B;
  printf("TRIANGULO: %.3lf\n", tri);
  printf("CIRCULO: %.3lf\n", cir);
  printf("TRAPEZIO: %.3lf\n", tra);
  printf("QUADRADO: %.3lf\n", qua);
  printf("RETANGULO: %.3lf\n", ret);
  return(0);
}
