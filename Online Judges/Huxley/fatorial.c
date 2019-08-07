#include <stdio.h>

int main()
{
  int n, fatorial;
  while (scanf("%i", &n) && n != -1)
  {
    for (fatorial = n - 1; fatorial > 1; fatorial --)
    {
      n *= fatorial;
    }
    if (n == 0)
    {
      n = 1;
    }
    printf("%i\n", n);
  }
  return(0);
}
