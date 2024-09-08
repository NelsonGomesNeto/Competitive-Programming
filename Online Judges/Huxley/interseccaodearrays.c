#include <stdio.h>

int main()
{
  int tam; scanf("%d", &tam);
  int a[tam], fim[tam], i, j, aux, posi = 0;
  for (i = 0; i < tam; i ++)
  {
    fim[i] = -1;
    scanf("%d", &a[i]);
  }
  int once;
  for (i = 0; i < tam; i ++)
  {
    scanf("%d", &aux);
    once = 0;
    for (j = 0; j < tam; j ++)
    {
      if (a[j] == aux)
      {
        fim[posi] = aux;
        if (once == 0)
        {
          posi ++; once ++;
        }
        a[j] = -1;
      }
    }
  }
  int o, b;
  for (o = 0; o < posi; o ++)
  {
    for (b = o; b < posi; b ++)
    {
      if (fim[b] < fim[o])
      {
        aux = fim[b];
        fim[b] = fim[o];
        fim[o] = aux;
      }
    }
  }
  for (o = 0; o < posi; o ++)
  {
    printf("%d\n", fim[o]);
  }
  return(0);
}
