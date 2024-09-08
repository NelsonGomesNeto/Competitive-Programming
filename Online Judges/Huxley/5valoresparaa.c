#include <stdio.h>

int main()
{
  float num; int ler, conta = 0;
  for (ler = 0; ler < 5; ler ++)
  {
    printf("Digite um valor:\n");
    scanf("%f", &num);
    if (num < 0)
    {
      conta ++;
    }
  }
  printf("Foram digitados %d numeros negativos\n", conta);
}
