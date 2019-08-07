#include <stdio.h>

int main()
{
  int n, mult3 = 0, mult5 = 0, soma = 0;
  scanf("%i", &n);
  while (mult3 < n)
  {
    soma += mult3;
    mult3 += 3;
  }
  while (mult5 < n)
  {
    if (mult5 % 3 == 0)
    {
      soma -= mult5;
    }
    soma += mult5;
    mult5 += 5;
  }
  printf("%i\n", soma);
  return(0);
}
