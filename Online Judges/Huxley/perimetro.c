#include <stdio.h>
#include <math.h>

int main()
{
  int lados; long double raio, per, angulo, pi = 3.14159265358979323846;
  scanf("%d\n%Lf", &lados, &raio);
  angulo = pi / lados;
  per = (2 * raio * sin(angulo)) * lados;
  printf("%.2Lf\n", per);
  return(0);
}
