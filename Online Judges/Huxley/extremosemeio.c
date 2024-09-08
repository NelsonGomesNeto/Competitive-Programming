#include <stdio.h>

int main()
{
  int tam; scanf("%d", &tam);
  int num[tam], ler, ordem, bubble, aux;
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &num[ler]);
  }
  for (ordem = 0; ordem < tam; ordem ++)
  {
    for (bubble = ordem; bubble < tam; bubble ++)
    {
      if (num[ordem] > num[bubble])
      {
        aux = num[ordem];
        num[ordem] = num[bubble];
        num[bubble] = aux;
      }
    }
  }
  printf("%d %d %d\n", num[0], num[tam/2], num[tam - 1]);
  return(0);
}
