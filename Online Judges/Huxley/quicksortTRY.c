#include <stdio.h>
#include <time.h>
#include <algorithm>
using namespace std;
int search(int a[], int num, int xI, int xF)
{
  if (num == a[(xF + xI) / 2])
  {
    return((xF + xI) / 2);
  }
  else if (num < a[(xF + xI) / 2])
  {
    search(a, num, xI, (xF + xI) / 2);
  }
  else
  {
    search(a, num, (xF + xI) / 2, xF);
  }
}

void quicksort(int a[], int first, int last)
{
  int pivor, i, j, aux;
  if (first < last)
  {
    pivor = first;
    i = first;
    j = last;
    while (i < j)
    {
      while (a[i] <= a[pivor] && i < last)
      {
        i ++;
      }
      while (a[j] > a[pivor])
      {
        j --;
      }
      if (i < j)
      {
        aux = a[i];
        a[i] = a[j];
        a[j] = aux;
      }
    }
    aux = a[pivor];
    a[pivor] = a[j];
    a[j] = aux;
    quicksort(a, first, j - 1);
    quicksort(a, j + 1, last);
  }
}

int main()
{
  int array[1000000], se, tam = 0;
  int i, posi, j;
  for (i = 999999, j = 0; i >= 0; i --, j ++)
  {
    array[j] = i;
  }
  clock_t elapsed = clock();
  quicksort(array, 0, 1000000 - 1);
  for (i = 0; i < 1000000; i += 10000)
  {
    posi = search(array, i, 0, 1000000);
  }
  elapsed = (clock() - elapsed);
  printf("%d found at %d in: %lf\n", array[posi], posi, ((double) elapsed)/CLOCKS_PER_SEC);
  return(0);
}
