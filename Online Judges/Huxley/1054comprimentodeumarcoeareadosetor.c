#include <stdio.h>
#include <math.h>

void printBug(double n)
{
  if ((int) round(n * 100) % 10 == 0)
    printf("%.1lf\n", round(n * 10) / 10);
  else
    printf("%.2lf\n", round(n * 100) / 100);
}

int main()
{
  double r, a, pi = 3.14;
  scanf("%lf\n%lf", &r, &a);

  printBug((a * 2 * pi * r) / 360);
  printBug((a * pi * r * r) / 360);
  return(0);
}
// 360 - pi*r�
// 10  - x
