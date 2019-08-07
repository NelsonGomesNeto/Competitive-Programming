#include <stdio.h>

int main()
{
  float a, b, c;
  scanf("%f\n%f\n%f", &a, &b, &c);
  printf("%f\n", ((a * b) / c));
  printf("%f\n", ((a * a) + b + (5 * c)));
  printf("%f\n", ((a*b*c) + b + ((c / 3) * 5) - 1));
  printf("%f\n", ((a*b*c) * (a*b*c) * (a*b*c)));
  return(0);
}
