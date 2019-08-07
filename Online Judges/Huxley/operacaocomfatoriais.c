#include <stdio.h>
#include <math.h>

long double fact(long double factX)
{
  int repeat;
  if (factX > 1)
  {
    factX *= fact(factX - 1);
  }
  return(factX);
}

long double main()
{
  int n; long double x, factX, soma;
  while (scanf("%LF %d", &x, &n) && !(x == 0 && n == 0))
  {
    soma = 0;
    while (n >= 1)
    {
      if (n % 2 == 0)
      {
        soma -= pow(x,(2 * (n - 1))) / fact((2 * (n - 1)) + 1);
      }
      else if (n > 1)
      {
        soma += pow(x,(2 * (n - 1))) / fact((2 * (n - 1)) + 1);
      }
      else
      {
        soma += x;
      }
      n --;
    }
    printf("%.6LF\n", soma);
  }
  return(0);
}
