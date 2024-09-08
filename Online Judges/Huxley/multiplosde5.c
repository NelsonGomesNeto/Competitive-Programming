#include <stdio.h>

int main()
{
  int n, m;
  scanf("%i %i", &n, &m);
  while (n <= m)
  {
    if (n % 5 == 0)
    {
      if (!(m - n >= 0 && m - n < 5))
      {
        printf("%i|", n);
      }
      else
      {
        printf("%i", n);
      }
    }
    n ++;
  }
  printf("\n");
  return(0);
}
