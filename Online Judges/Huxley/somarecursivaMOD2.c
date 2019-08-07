#include <stdio.h>

int soma_rec(int a[], int i, int tofound)
{
  if (a[i] == tofound || i == 0)
  {
    return(i);
  }
  soma_rec(a, i - 1, tofound);
}

int main()
{
  int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int search; scanf("%d", &search);
  int posi = soma_rec(array, 10 - 1, search);
  printf("array[%d] = %d\n", posi, array[posi]);
}
