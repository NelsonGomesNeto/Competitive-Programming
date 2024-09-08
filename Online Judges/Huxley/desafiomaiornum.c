#include <stdio.h>

int main()
{
  int numero, maiorN;
  scanf("%i", &numero);
  maiorN = numero;
  while (numero != 0)
  {
    scanf("%i", &numero);
    if (numero > maiorN)
    {
      maiorN = numero;
    }
  }
  printf("%i\n", maiorN);
  return(0);
}
