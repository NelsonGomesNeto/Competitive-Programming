#include <stdio.h>

int main()
{
  int n, fibA, fibB, aux;
  while (scanf("%d", &n) && n != 0)
  {
    fibA = 0; fibB = 1;
    while (n > 1)
    {
      printf("%d ", fibA);
      aux = fibA;
      fibA += fibB;
      fibB = aux;
      n --;
    }
    printf("%d\n", fibA);
  }
  return(0);
}
