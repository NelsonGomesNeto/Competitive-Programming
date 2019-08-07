#include <stdio.h>

int main()
{
  int dinheiro;
  int reais50 = 0, reais20 = 0, reais10 = 0, reais5 = 0, reais1 = 0;
  scanf("%i", &dinheiro);
  while (dinheiro > 0)
  {
    if (dinheiro >= 50)
    {
      reais50 ++;
      dinheiro -= 50;
    }
    else if (dinheiro >= 20)
    {
      reais20 ++;
      dinheiro -= 20;
    }
    else if (dinheiro >= 10)
    {
      reais10 ++;
      dinheiro -= 10;
    }
    else if (dinheiro >= 5)
    {
      reais5 ++;
      dinheiro -= 5;
    }
    else if (dinheiro >= 1)
    {
      reais1 ++;
      dinheiro -= 1;
    }
  }
  printf("Notas de 50: %i\n", reais50);
  printf("Notas de 20: %i\n", reais20);
  printf("Notas de 10: %i\n", reais10);
  printf("Notas de 5: %i\n", reais5);
  printf("Notas de 1: %i\n", reais1);
  return(0);
}
