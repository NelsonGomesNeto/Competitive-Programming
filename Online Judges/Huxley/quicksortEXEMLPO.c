#include <stdio.h>
#include <math.h>

void quicksort(int num[], int first, int last)
{
  int pivot, j, i, aux;
  if (first < last)
  {
    pivot = first;
    i = first;
    j = last;
    while (i < j)
    {
      while (num[i] <= num[pivot] && i < last) // <= Para crescente
      {
        i ++;
      }
      while (num[j] > num[pivot]) // > Para crescente
      {
        j --;
      }
      if (i < j)
      {
        aux = num[i];
        num[i] = num[j];
        num[j] = aux;
      }
    }
    aux = num[pivot];
    num[pivot] = num[j];
    num[j] = aux;
    quicksort(num, first, j - 1);
    quicksort(num, j + 1, last);
  }
}

int main()
{
  int tam; scanf("%d", &tam);
  int array[tam], ler;
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &array[ler]);
  }
  quicksort(array, 0, tam - 1);
  for (ler = 0; ler < tam; ler ++)
  {
    printf("%d ", array[ler]);
  }
  printf("\n");
  return(0);
}
