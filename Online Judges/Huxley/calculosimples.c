#include <stdio.h>

int main()
{
  int codigo, quant; float preco, total = 0;
  scanf("%i %i %f", &codigo, &quant, &preco);
  total += preco * quant;
  scanf("%i %i %f", &codigo, &quant, &preco);
  total += preco * quant;
  printf("VALOR A PAGAR: R$ %.2f\n", total);
  return(0);
}
