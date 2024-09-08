#include <stdio.h>

int main()
{
  int a[4];
  scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]);
  int i, j, somaA = 0, somaB = 0, soma, clean;
  for (i = 0; i < 4; i ++)
  {
    for (j = 0; j < 4; j ++)
    {
      if (i != j)
      {
        soma = a[i] + a[j];
        if (somaA == 0 || soma < somaA)
        {
          somaA = soma;
          clean = a[i] > a[j] ? i : j;
        }
      }
    }
  }
  for (i = 0; i < 4; i ++)
  {
    for (j = 0; j < 4; j ++)
    {
      if (i != j && i != clean && j != clean)
      {
        soma = a[i] + a[j];
        if (somaB == 0 || soma < somaB)
        {
          somaB = soma;
        }
      }
    }
  }
  printf("%d%d\n", somaA, somaB);
  return(0);
}
