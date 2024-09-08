#include <stdio.h>

int dpMaxSum(int a[], int start, int tam)
{
  int i, loop, sum = 0, maxSum = -999999;
  for (i = start, loop = 0; loop < tam; loop ++, i ++)
  {
    i %= tam;
    sum += a[i];
    if (sum > maxSum)
      maxSum = sum;
    if (sum < 0)
      sum = 0;
  }
  return(maxSum);
}

int main()
{
  int tam; scanf("%d", &tam);
  int array[tam * 2 + 1], i;

  for (i = 0; i < tam; i ++)
  {
    scanf("%d", &array[i]);
    array[i + tam] = array[i];
  }

  int biggest = -999999, aux;
  for (i = 0; i < tam; i ++)
  {
    aux = dpMaxSum(array, i, tam);
    if (aux > biggest)
      biggest = aux;
  }

  printf("%d\n", biggest);

  return(0);
}
