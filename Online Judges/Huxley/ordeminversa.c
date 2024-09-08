#include <stdio.h>

int main()
{
  float array[10]; int ler;
  for (ler = 0; ler < 10; ler ++)
  {
    printf("Digite um numero:\n");
    scanf("%g", &array[ler]);
  }
  for (ler = 9; ler >= 0; ler --)
  {
    if (array[ler] - (int) array[ler] != 0)
    {
      printf("%g\n", array[ler]);
    }
    else
    {
      printf("%g.0\n", array[ler]);
    }
  }
  return(0);
}
