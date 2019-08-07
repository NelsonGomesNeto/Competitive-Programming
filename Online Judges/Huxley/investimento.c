#include <stdio.h>

int main()
{
  float valor, taxa, rende; int anos;
  scanf("%f %f %d", &valor, &taxa, &anos);
  anos *= 4;
  while (anos > 0)
  {
    rende = valor * taxa;
    valor += rende;
    printf("Rendimento: %.2f Montante: %.2f\n", rende, valor);
    anos --;
  }
  return(0);
}
