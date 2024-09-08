#include <stdio.h>

int main()
{
  int maior, sec, aux, i, swap = 0;
  for (i = 0; i < 10; i ++)
  {
    scanf("%d", &aux);
    if (i == 0)
    {
      maior = aux;
    }
    if (i == 1)
    {
      sec = aux;
    }
    if (sec > maior)
    {
      swap = sec;
      sec = maior;
      maior = swap;
    }
    else if (aux >= maior)
    {
      swap = maior;
      maior = aux;
      sec = swap;
    }
    if (aux > sec && aux < maior)
    {
      sec = aux;
    }
  }
  printf("%d\n%d\n", maior, sec);
  return(0);
}
