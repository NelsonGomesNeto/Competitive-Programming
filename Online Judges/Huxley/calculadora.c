#include <stdio.h>

int main()
{
  float a, b;
  scanf("%f\n%f", &a, &b);
  printf("%f\n%f\n%f\n%f\n", (a * b), (a / b), (a + b), (a - b));
  return(0);
}
