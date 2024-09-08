#include <stdio.h>

int main()
{
  double salario; scanf("%lf", &salario);
  if (salario < 1000)
  {
    salario *= 1.3;
  }
  else if (salario <= 2000)
  {
    salario *= 1.1;
  }
  printf("%.2lf\n", salario);
  return(0);
}
