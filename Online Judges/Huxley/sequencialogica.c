#include <stdio.h>

int main()
{
  int N, n1 = 0, n2 = 1, n3;
  scanf("%i", &N); N *= 2;
  while (N > 0)
  {
    if (N % 2 == 0)
    {
      n1 += 1; n2 = n1 * n1; n3 = n1 * n2;
    }
    else
    {
      n2 += 1; n3 += 1;
    }
    printf("%i %i %i\n", n1, n2, n3);
    N --;
  }
  return(0);
}
