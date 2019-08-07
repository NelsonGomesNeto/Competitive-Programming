#include <stdio.h>

int main()
{
  float numA, numB, soma;
  printf("Digite um numero:\nDigite outro numero:\n");
  scanf("%f\n%f", &numA, &numB);
  soma = numA + numB;
  printf("Soma: %.1f\n", soma);
  return(0);
}
