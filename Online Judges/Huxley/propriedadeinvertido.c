#include <stdio.h>

int main()
{
  int nini, n10, nfim, mod = 1;
  scanf("%i %i", &nini, &nfim);
  while (nini <= nfim)
  {
    mod = (nini / 10) - ((nini % 10) / 10);
    if ((nini % mod == 0) && (nini % 10 != 0))
    {
      printf("%i\n", nini);
    }
    nini ++;
  }
  return(0);
}
