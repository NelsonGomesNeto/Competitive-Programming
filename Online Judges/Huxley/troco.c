#include <stdio.h>

int main()
{
  int din, troco;
  scanf("%i", &din);
  while (din >= 7)
  {
    troco = din - 7;
    din -= 7;
  }
  printf("%i\n", troco);
  return(0);
}
