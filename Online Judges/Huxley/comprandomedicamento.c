#include <stdio.h>

int main()
{
  int caixas; scanf("%i", &caixas);
  int dias, sobra;
  dias = (caixas * 35) / 4;
  sobra = (caixas * 35) % 4;
  printf("%i\n%i\n", dias, sobra);
  return(0);
}
