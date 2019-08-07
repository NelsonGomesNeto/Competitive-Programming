#include <stdio.h>
#include <string.h>

int main()
{
  int quantidade, repeat, capsulas = 0, chicaras;
  char tamanho;
  for (repeat = 0; repeat < 7; repeat ++)
  {
    scanf("%i\n%c", &quantidade, &tamanho);
    if (tamanho == 'p' || tamanho == 'P')
    {
      capsulas += 10 * quantidade;
    }
    else
    {
      capsulas += 16 * quantidade;
    }
  }
  chicaras = (capsulas * 2) / 7;
  printf("%i\n%i\n", capsulas, chicaras);
  return(0);
}
