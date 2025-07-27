#include <stdio.h>

int main()
{
  int ini, nuse, nini, nfim, fim, steps = 1, stepsmaior;
  while (scanf("%d %d", &ini, &fim) == 2)
  {
    if (ini >= fim)
    {
      nfim = fim;
      nuse = nfim;
      nini = 0;
    }
    else
    {
      nini = ini;
      nuse = nini;
      nfim = 0;
    }
    stepsmaior = 1;
    while (nini <= fim && nfim <= ini)
    {
      while (nuse != 1)
      {
        if (nuse % 2 == 0)
        {
          nuse = nuse / 2;
          steps ++;
        }
        else
        {
          nuse = (3 * nuse) + 1;
          steps ++;
        }
      }
      if (steps > stepsmaior)
      {
        stepsmaior = steps;
      }
      steps = 1;
      if (nini > 0)
      {
        nini ++;
        nuse = nini;
      }
      else if (nfim > 0)
      {
        nfim ++;
        nuse = nfim;
      }
    }
    printf("%d %d %d\n", ini, fim, stepsmaior);
  }
  return(0);
}
