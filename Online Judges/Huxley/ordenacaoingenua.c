#include <stdio.h>

int main()
{
  int numeros, ler; scanf("%d", &numeros);
  int array[numeros], ordem, bubble, aux;
  for (ler = 0; ler < numeros; ler ++)
  {
    scanf("%d", &array[ler]);
  }
  for (ordem = 0; ordem < numeros; ordem ++)
  {
    for (bubble = ordem; bubble < numeros; bubble ++)
    {
      if (array[ordem] > array[bubble])
      {
        aux = array[ordem];
        array[ordem] = array[bubble];
        array[bubble] = aux;
      }
    }
  }
  for (ordem = 0; ordem < numeros; ordem ++)
  {
    printf("[%d]", array[ordem]);
  }
  printf("\n");
  return(0);
}
