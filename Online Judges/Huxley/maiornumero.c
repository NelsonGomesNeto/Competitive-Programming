#include <stdio.h>

int main()
{
  float num, maior; int ler;
  for (ler = 0; ler < 50; ler ++)
  {
    printf("Digite um numero:\n");
    scanf("%f", &num);
    if (ler == 0 || num > maior)
    {
      maior = num;
    }
  }
  printf("Maior numero: %.2f\n", maior);
  return(0);
}
