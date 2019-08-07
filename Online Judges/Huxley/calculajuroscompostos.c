#include <stdio.h>

int main()
{
  int meses; long double taxa, valor, total;
  scanf("%d\n%LF\n%LF", &meses, &taxa, &valor);
  total = valor;
  while (meses > 0)
  {
    total *= (taxa + 1);
    meses --;
  }
  printf("%.2LF\n", total);
  return(0);
}
