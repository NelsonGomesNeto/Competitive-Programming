#include <stdio.h>

int main()
{
  double a, b; scanf("%lf\n%lf", &a, &b);

  if (a > b)
    printf("Primeiro circulo\n");
  else if (a < b)
    printf("Segundo circulo\n");
  else
    printf("Iguais\n");

  return(0);
}
