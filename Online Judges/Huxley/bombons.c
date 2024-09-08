#include <stdio.h>

int main()
{
  int preco[3], bombom[3], repeat;
  float total = 0;
  for (repeat = 0; repeat < 3; repeat ++)
  {
    scanf("%i", &preco[repeat]);
  }
  for (repeat = 0; repeat < 3; repeat ++)
  {
    scanf("%i", &bombom[repeat]);
  }
  for (repeat = 0; repeat < 3; repeat ++)
  {
    total += preco[repeat] * bombom[repeat];
  }
  printf("Valor: R$%.2f\n", total);
  return(0);
}
