#include <stdio.h>

int main()
{
  printf("Digite uma temperatura na escala Fahrenheit:\n");
  double fah, c; scanf("%lf", &fah);
  c = (5 * (fah - 32) / 9);
  printf("Temperatura em Celsius: %.1lf\n", c);
  return(0);
}
