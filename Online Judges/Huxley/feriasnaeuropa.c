#include <stdio.h>

int main()
{
  int dias; float custo;
  scanf("%i", &dias);
  custo = ((dias * 20) * 3.2);
  printf("%.2f\n", custo);
  return(0);
}
