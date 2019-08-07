#include <stdio.h>
#include <math.h>

int n; long double x = 0, factX;

long double fact(long double factX)
{
  int repeat;
  for (repeat = factX - 1; repeat > 1; repeat --)
  {
    factX *= repeat;
  }
  return(factX);
}

int main()
{
  scanf("%i", &n);
  while (n > 0)
  {
    if (n % 2 == 0)
    {
      x -= (fact(n) / (pow(2,n) - 1));
    }
    else if (n > 1)
    {
      x += (fact(n) / (pow(2,n) - 1));
    }
    else
    {
      x += 1;
    }
    n --;
  }
  printf("%.2LF\n", x);
  return(0);
}
