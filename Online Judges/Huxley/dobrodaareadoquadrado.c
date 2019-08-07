#include <stdio.h>

int main()
{
  float lado;
  printf("Informe a medida de um dos lados do quadrado:\n");
  scanf("%f", &lado); float quad = lado * lado;
  printf("Resultado: %.1f\n", quad);
  printf("Dobro: %.1f\n", quad * 2);
  return(0);
}
