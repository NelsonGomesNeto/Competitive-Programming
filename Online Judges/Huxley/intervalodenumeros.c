#include <stdio.h>

int main()
{
  int num, a = 0, b = 0, c = 0, d = 0;
  printf("Digite um numero inteiro:\n");
  while (scanf("%d", &num) && num >= 0)
  {
    printf("Digite um numero inteiro:\n");
    if (num <= 25)
    {
      a ++;
    }
    else if (num <= 50)
    {
      b ++;
    }
    else if (num <= 75)
    {
      c ++;
    }
    else if (num <= 100)
    {
      d ++;
    }
  }
  printf("Quantidade de numeros no intervalo 1: %d\n", a);
  printf("Quantidade de numeros no intervalo 2: %d\n", b);
  printf("Quantidade de numeros no intervalo 3: %d\n", c);
  printf("Quantidade de numeros no intervalo 4: %d\n", d);
  return(0);
}
