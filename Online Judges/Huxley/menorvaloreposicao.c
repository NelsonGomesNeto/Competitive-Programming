#include <stdio.h>

int main()
{
  int tamanho, menor, posi;
  scanf("%i", &tamanho);
  int num[tamanho], repeat;
  for (repeat = 0; repeat < tamanho; repeat ++)
  {
    scanf("%i", &num[repeat]);
    if (repeat == 0 || num[repeat] < menor)
    {
      menor = num[repeat];
      posi = repeat;
    }
  }
  printf("Menor valor: %i\nPosicao: %i\n", menor, posi);
  return(0);
}
