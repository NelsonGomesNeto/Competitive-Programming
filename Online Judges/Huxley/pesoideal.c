#include <stdio.h>

int main()
{
  printf("Informe sua altura:\n");
  double altura; scanf("%lf", &altura);
  altura = (72.7 * altura) - 58;
  printf("Peso ideal: %.14lf\n", altura);
  return(0);
}
