#include <stdio.h>

int main()
{
  float celsius, fahrenheit;
  scanf("%f", &fahrenheit);
  celsius = ((fahrenheit - 32) * 5) / 9;
  printf("%.2f\n", celsius);
  return(0);
}
