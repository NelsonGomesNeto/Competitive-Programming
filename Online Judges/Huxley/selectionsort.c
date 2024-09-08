#include <stdio.h>

void printarPasso(int a[], int min, int end)
{
  printf("Menor elemento neste passo: %d\n", min);
  printf("Estado Atual:"); int i;
  for (i = 0; i < end - 1; i ++)
  {
    printf(" %d |", a[i]);
  } printf(" %d\n\n", a[i]);
}

void swap(int *a, int *b)
{
  int aux = (*a);
  (*a) = (*b);
  (*b) = aux;
}

int findMin(int a[], int start, int end)
{
  int min = a[start], posi = start, i;
  for (i = start + 1; i < end; i ++)
  {

    if (a[i] < min)
    {
      min = a[i];
      posi = i;
    }
  }
  return(posi);
}

void selectionSort(int a[], int end)
{
  int i, j;
  for (i = 0; i < end; i ++)
  {
    j = findMin(a, i, end);
    swap(&a[i], &a[j]);
    if (i < end - 1)
      printarPasso(a, a[i], end);
  }
}

int main()
{
  int array[100000], i = 0;
  while (scanf("%d", &array[i]) != EOF)
  {
    i ++;
  }
  selectionSort(array, i);
  printf("Resultado Final:"); int j;
  for (j = 0; j < i - 1; j ++)
  {
    printf(" %d |", array[j]);
  } printf(" %d\n", array[j]);
  return(0);
}
