#include <stdio.h>

int main()
{
  float peso, h, IMC;
  scanf("%f\n%f", &peso, &h);
  IMC = peso / (h*h);
  printf("%f\n", IMC);
  return(0);
}
