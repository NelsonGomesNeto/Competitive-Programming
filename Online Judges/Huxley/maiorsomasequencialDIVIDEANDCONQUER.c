#include <stdio.h>

int max(int a, int b)
{
  return(a > b ? a : b);
}

int divideAndConquer(int a[], int start, int end)
{
  if (start == end)
    return(a[start]);

  int mid = (start + end) / 2, i;
  int sum = 0, bestLeft, bestRight;
  bestLeft = bestRight = -9999999;

  for (i = mid; i >= start; i --)
  {
    sum += a[i];
    if (sum > bestLeft)
      bestLeft = sum;
  }

  sum = 0;
  for (i = mid + 1; i <= end; i ++)
  {
    sum += a[i];
    if (sum > bestRight)
      bestRight = sum;
  }

  return(max(max(divideAndConquer(a, start, mid), divideAndConquer(a, mid + 1, end)), bestLeft + bestRight));
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
    aux = divideAndConquer(array, i, tam - 1 + i);
    if (aux > biggest)
      biggest = aux;
  }

  printf("%d\n", biggest);

  return(0);
}
