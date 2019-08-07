#include <stdio.h>

int main()
{
  int num[1000000], ler = 0, ordem, bubble, aux;
  while (scanf("%d", &num[ler]) && num[ler] != 99)
  {
    ler ++;
  }
  for (ordem = 0; ordem <= ler; ordem ++)
  {
    for (bubble = ordem; bubble <= ler; bubble ++)
    {
      if (num[ordem] < num[bubble])
      {
        aux = num[ordem];
        num[ordem] = num[bubble];
        num[bubble] = aux;
      }
    }
  }
  printf("%d\n", num[2]);
  return(0);
}
