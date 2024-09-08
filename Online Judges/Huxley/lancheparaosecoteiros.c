#include <stdio.h>

int main()
{
  int escoteiro; scanf("%i", &escoteiro);
  float preco;
  preco = (2 * (escoteiro * (4.15 / 23))) + (escoteiro * (3.89 / 8));
  printf("%.2f\n", preco);
  return(0);
}
