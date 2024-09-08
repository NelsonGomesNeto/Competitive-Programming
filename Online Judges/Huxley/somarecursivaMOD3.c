#include <stdio.h>

int soma_rec(int a[], int i, int tam, int maior)
{
  if (i == 0 || a[i] > maior)
  {
    maior = a[i];
  }
  if (i == tam - 1)
  {
    return(i);
  }
  soma_rec(a, i + 1, tam, maior);
}

int main()
{
  int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int posi = soma_rec(array, 0, 10, 0);
  printf("array[%d] = %d\n", posi, array[posi]);
}
