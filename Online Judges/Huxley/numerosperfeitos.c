#include <stdio.h>

int main()
{
  int n, nfim, divi, teste = 0;
  scanf("%i", &n);
  nfim = n;
  n = 0;
  divi = n + 1;
  while (n < nfim)
  {
    if (!(divi == 0))
    {
      divi --;
    }
    if (divi == 0)
    {
      n ++;
      divi = n;
      teste = 0;
    }
    if (n % divi == 0)
    {
      teste += divi;
    }
    if (2 * n == teste && divi == 1)
    {
      printf("%i\n", (teste / 2));
    }
  }
  return(0);
}
