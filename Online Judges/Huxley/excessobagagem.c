#include <stdio.h>

int main()
{
  float peso, conta = 0;
  scanf("%f", &peso);
  if (peso <= 20)
  {
    printf("0.00\n");
  }
  else if (peso > 20 && peso <= 25)
  {
    conta = 12.5 * (peso - 20);
    printf("%.2f\n", conta);
  }
  else if (peso > 25 && peso <= 30)
  {
    conta = 32.75 * (peso - 20);
    printf("%.2f\n", conta);
  }
  else if (peso > 30)
  {
    printf("PESO LIMITE EXCEDIDO\n");
  }
  return(0);
}
