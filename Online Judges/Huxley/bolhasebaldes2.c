#include <stdio.h>
#include <math.h>

#include <stdio.h>

//Merge sort
void mergeSort(int array[], int begin, int end, int *w)
{
  int i, j, k, meio, aux[end + 1];
  if (begin == end)
  {
    return;
  }
  //ordenacao recursiva das duas metades
  meio = (begin + end) / 2;
  mergeSort(array, begin, meio, &*w);
  mergeSort(array, meio + 1, end, &*w);

  i = begin;
  j = meio + 1;
  k = 0;

  while (i < meio + 1 || j < end + 1)
  {
    if (i == meio + 1) //i passou do final da primeira metade, pegar array[j]
    {
      aux[k] = array[j];
      (*w) += (j - k);
      j ++;
      k ++;
    }
    else
    {
      if (j == end + 1) //j passou do final da segunda metade, pegar array[i];
      {
        aux[k] = array[i];
        (*w) += (i - k);
        i ++;
        k ++;
      }
      else
      {
        if (array[i] < array[j])
        {
          aux[k] = array[i];
          (*w) += (i - k);
          i ++;
          k ++;
        }
        else
        {
          aux[k] = array[j];
          (*w) += (j - k);
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
  int numeros;
  while (scanf("%d", &numeros) && numeros != 0)
  {
    int ler, array[numeros], win = 0;
    for (ler = 0; ler < numeros; ler ++)
    {
      scanf("%d", &array[ler]);
    }
    mergeSort(array, 0, numeros - 1, &win);
    printf("%d\n", win);
    if (win % 2 != 0)
    {
      printf("Marcelo\n");
    }
    else
    {
      printf("Carlos\n");
    }
  }
  return(0);
}
