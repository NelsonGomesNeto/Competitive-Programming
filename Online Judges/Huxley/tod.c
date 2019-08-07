#include <stdio.h>

int check(int a[], int fim)
{
  int i, j, conta;
  for(i = 1; i <= fim; i ++)
  {
    conta = 0;
    for (j = 0; j < fim; j ++)
    {
      if (a[j] == i)
      {
        conta ++;
      }
      if (conta > 1)
      {
        return(0);
      }
    }
  }
  return(1);
}

void backtrack(int a[], int i, int fim)
{
  if (i == fim)
  {
    if (check(a, fim) == 1)
    {
      int j;
      for (j = 0; j < fim; j ++)
      {
        printf("%d", a[j]);
      } printf("\n");
    }
    return;
  }
  int numeros;
  for (numeros = 1; numeros <= fim; numeros ++)
  {
    a[i] = numeros;
    backtrack(a, i + 1, fim);
  }
}

int main()
{
  int num; scanf("%d", &num);
  int array[num];
  backtrack(array, 0, num);
  return(0);
}
