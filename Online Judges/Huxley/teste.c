#include <stdio.h>
#include <math.h>

int main()
{
  float teste = 32.7008;
  teste = (round((teste * 100) + 0.1))/100;
  printf("%.2f\n", (round(teste * 100))/100);
  return(0);
}
