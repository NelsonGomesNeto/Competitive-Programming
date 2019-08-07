#include <stdio.h>

int main()
{
  float metros, cent;
  printf("Insira um valor em metros:\n");
  scanf("%f", &metros);
  cent = metros * 100;
  printf("Resultado: %.1f\n", cent);
  return(0);
}
