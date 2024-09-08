#include <stdio.h>

int main()
{
  int impar[5], par[5], num, ler, printar, impares = 0, pares = 0;
  for (ler = 0; ler < 15; ler ++)
  {
    scanf("%d", &num);
    if (num % 2 == 0)
    {
      par[pares] = num;
      pares ++;
    }
    else
    {
      impar[impares] = num;
      impares ++;
    }
    if (pares == 5)
    {
      for (printar = 0; printar < pares; printar ++)
      {
        printf("par[%d] = %d\n", printar, par[printar]);
      }
      pares = 0;
    }
    if (impares == 5)
    {
      for (printar = 0; printar < impares; printar ++)
      {
        printf("impar[%d] = %d\n", printar, impar[printar]);
      }
      impares = 0;
    }
  }
  for (printar = 0; printar < impares; printar ++)
  {
    printf("impar[%d] = %d\n", printar, impar[printar]);
  }
  for (printar = 0; printar < pares; printar ++)
  {
    printf("par[%d] = %d\n", printar, par[printar]);
  }
  return(0);
}
