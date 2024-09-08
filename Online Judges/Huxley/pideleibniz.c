#include <stdio.h>
#include <math.h>

int main()
{
  double pi = 0;
  int ate, i, sum; scanf("%d", &ate);
  for (i = 0, sum = 1; i < ate; i ++)
  {
    pi += ((double) 1 / (double) (sum * ((2 * i) + 1)));
    sum *= -1;
  }
  pi *= 4;

  printf("%.5lf\n", pi);
  return(0);
}
