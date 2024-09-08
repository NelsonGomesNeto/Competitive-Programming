#include <stdio.h>

int main()
{
  double pi = 3.1416, vol, A, R;
  scanf("%lf", &R);
  A = 4 * pi * R * R;
  vol = (4 * pi * R * R * R) / 3;
  printf("%.2lf\n%.2f\n", A, vol);
  return(0);
}
