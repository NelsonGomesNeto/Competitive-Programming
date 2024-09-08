#include <stdio.h>
#include <math.h>

double eleva(double x, double y)
{
  double num = x;
  while (y > 1)
  {
    num *= x;
    y --;
  }
  return(num);
}

int main()
{
  double valor, juros, total; int prest;
  scanf("%lf\n%d\n%lf", &valor, &prest, &juros);
  total = floor(valor / ((eleva((1 + juros),prest) - 1) / (juros * eleva((1 + juros), prest))));
  printf("%.0f\n", total);
  return(0);
}
