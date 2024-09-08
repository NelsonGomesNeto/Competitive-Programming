#include <stdio.h>

int main()
{
  int dias; float multa;
  scanf("%i", &dias);
  multa = dias * 0.75;
  printf("%.2f\n", multa);
  return(0);
}
