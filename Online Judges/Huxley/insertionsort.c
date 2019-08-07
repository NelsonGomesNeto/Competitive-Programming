#include <stdio.h>

void printarArray(int a[], int end)
{
  int i;
  for (i = 0; i < end - 1; i ++)
  {
    printf("%d | ", a[i]);
  } printf("%d\n", a[i]);
}

void swap(int *a, int *b)
{
  int aux = (*a);
  (*a) = (*b);
  (*b) = aux;
}

int realocate(int a[], int i, int end)
{
  printf("Estado Atual: ");
  while (i > 0 && a[i] < a[i - 1])
  {
    printarArray(a, end);
    swap(&a[i], &a[i - 1]);
    i --;
  }
  printarArray(a, end);
}

void insertionSort(int a[], int end)
{
  int i, j;
  for (i = 0, j = 1; i < end - 1; i ++, j ++)
  {
    printf("Chave: %d\n", a[j]);
    realocate(a, j, end);
    printf("\n");
  }
}

int main()
{
  int array[100000], i = 0;
  while (scanf("%d", &array[i]) != EOF)
  {
    i ++;
  }
  insertionSort(array, i);
  printf("Resultado Final:"); int j;
  for (j = 0; j < i - 1; j ++)
  {
    printf(" %d |", array[j]);
  } printf(" %d\n", array[j]);
  return(0);
}
