#include <stdio.h>

int main()
{
  float num;
  printf("Informe uma nota entre 0 e 10:\n");
  while (scanf("%f", &num) && !(num >= 0 && num <= 10))
  {
    printf("Valor invalido\n");
    printf("Informe uma nota entre 0 e 10:\n");
  }
  return(0);
}
