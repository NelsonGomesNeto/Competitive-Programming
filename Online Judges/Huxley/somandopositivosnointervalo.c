#include <stdio.h>

int main()
{
  int numA, numB, aux, soma = 0;
  scanf("%d\n%d", &numA, &numB);
  if (numA > numB)
  {
    aux = numB;
    numB = numA;
    numA = aux;
  }
  while (numB >= numA && numB > 0)
  {
    soma += numB;
    numB --;
  }
  printf("%d\n", soma);
  return(0);
}
