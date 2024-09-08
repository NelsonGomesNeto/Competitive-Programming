#include <stdio.h>

int main()
{
  int num[10], ler = 0, ordem, bubble, aux;
  for (ler = 0; ler < 10; ler ++)
  {
    scanf("%d", &num[ler]);
  }
  for (ordem = 0; ordem < ler; ordem ++)
  {
    for (bubble = ordem; bubble < ler; bubble ++)
    {
      if (num[ordem] < num[bubble])
      {
        aux = num[ordem];
        num[ordem] = num[bubble];
        num[bubble] = aux;
      }
    }
  }
  printf("%d\n", num[0]);
  return(0);
}
