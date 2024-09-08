#include <stdio.h>

int main()
{
  float raio, area, pi = 3.14159; scanf("%f", &raio);
  area = (raio * raio * pi) / 10000;
  printf("Area = %.4f\n", area);
  return(0);
}
