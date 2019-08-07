#include <stdio.h>

int check(int a[], int atual, int fim)
{
  int i;
  for (i = 0; i < fim; i ++)
  {
    if (a[i] == atual)
    {
      return(0);
    }
  }
  return(1);
}

void backtrack(int a[], int i, int fim)
{
  if (i == fim)
  {
      int j;
      for (j = 0; j < fim; j ++)
      {
        printf("%d", a[j]);
      } printf("\n");
    return;
  }
  int numeros;
  for (numeros = 1; numeros <= fim; numeros ++)
  {
    if (check(a, numeros, i) == 1)
    {
      a[i] = numeros;
      backtrack(a, i + 1, fim);
    }
  }
}

int main()
{
  int num; scanf("%d", &num);
  int array[num], i;
  backtrack(array, 0, num);
  return(0);
}
