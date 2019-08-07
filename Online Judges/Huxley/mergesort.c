#include <stdio.h>

//Merge sort
void mergeSort(int array[], int begin, int end)
{
  int i, j, k, meio, aux[end + 1];
  if (begin == end)
  {
    return;
  }
  //ordenacao recursiva das duas metades
  meio = (begin + end) / 2;
  mergeSort(array, begin, meio);
  mergeSort(array, meio + 1, end);

  i = begin;
  j = meio + 1;
  k = 0;

  while (i < meio + 1 || j < end + 1)
  {
    if (i == meio + 1) //i passou do final da primeira metade, pegar array[j]
    {
      aux[k] = array[j];
      j ++;
      k ++;
    }
    else
    {
      if (j == end + 1) //j passou do final da segunda metade, pegar array[i];
      {
        aux[k] = array[i];
        i ++;
        k ++;
      }
      else
      {
        if (array[i] < array[j])
        {
          aux[k] = array[i];
          i ++;
          k ++;
        }
        else
        {
          aux[k] = array[j];
          j ++;
          k ++;
        }
      }
    }
  }
  //copia aux para array
  for (i = begin; i <= end; i ++)
  {
    array[i] = aux[i - begin];
  }
}

int main()
{
  int a[10] = {9, 2, 3, 5, 4, 6, 1, 8, 7, 10};
  mergeSort(a, 0, 9);
  int i;
  for (i = 0; i < 10; i ++)
  {
    printf("%d ", a[i]);
  }
  printf("\n");
  return(0);
}
