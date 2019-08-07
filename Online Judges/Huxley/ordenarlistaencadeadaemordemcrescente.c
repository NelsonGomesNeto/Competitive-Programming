#include <stdio.h>

int main()
{
  int num[500], tam = 0, ordem, bubble, aux;
  while (scanf("%d", &num[tam]) != EOF)
  {
    tam ++;
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
  for (ordem = 0; ordem < tam - 1; ordem ++)
  {
    printf("%d ", num[ordem]);
  }
  printf("%d\n", num[ordem]);
  return(0);
}
