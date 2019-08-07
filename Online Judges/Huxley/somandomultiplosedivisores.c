#include <stdio.h>

int main()
{
  int numA, numB, aux, soma = 0;
  scanf("%i\n%i", &numA, &numB);
  if (numB < numA)
  {
    aux = numA;
    numA = numB;
    numB = aux;
  }
  while (numA < numB - 1)
  {
    numA ++;
    if (1000 % numA == 0 && numA % 4 == 0)
    {
      soma += numA;
    }
  }
  printf("%i\n", soma);
  return(0);
}
