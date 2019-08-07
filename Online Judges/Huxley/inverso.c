#include <stdio.h>

int main()
{
  int tamanho, inv; scanf("%d", &tamanho);
  int N[tamanho]; inv = tamanho;
  for (tamanho = 0; tamanho < inv; tamanho ++)
  {
    scanf("%d", &N[tamanho]);
  }
  while (inv > 1)
  {
    printf("%d ", N[inv - 1]);
    inv --;
  }
  printf("%d\n", N[0]);
  return(0);
}
