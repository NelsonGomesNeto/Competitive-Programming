#include <stdio.h>

int soma_rec(int a[], int i, int tam)
{
  if (i == tam - 1)
  {
    return(a[i]);
  }
  return(a[i] + soma_rec(a, i + 1, tam));
}

int main()
{
  int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int soma = soma_rec(array, 0, 10);
  printf("%d\n", soma);
}
