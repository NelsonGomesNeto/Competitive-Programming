#include <stdio.h>

void backtrack(int a[], int i, int fim)
{
  if (i == fim)
  {
    int j;
    printf("{ ");
    for (j = 0; j < fim; j ++)
    {
      if (a[j] == 1)
      {
        printf("%d ", j + 1);
      }
    }
    printf("}\n");
    return;
  }
  int numeros;
  for (numeros = 1; numeros >= 0; numeros --)
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
