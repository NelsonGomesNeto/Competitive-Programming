#include <stdio.h>

int main()
{
  int X, Z, soma, nvezes = 1;
  scanf("%i\n%i", &X, &Z);
  soma = X;
  while (Z <= X)
  {
    scanf("%i", &Z);
  }
  while (soma <= Z)
  {
    X ++;
    soma += X;
    nvezes ++;
  }
  printf("%i\n", nvezes);
  return(0);
}
