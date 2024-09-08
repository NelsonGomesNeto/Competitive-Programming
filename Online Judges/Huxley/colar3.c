#include <stdio.h>
#include <string.h>

int main()
{
  int tam, run;
  scanf("%d", &tam);
  char colar[tam + 20], corA, corB;
  getchar(); scanf("%s", colar);
  int pedra, maior = 0, posi, noW, max, lim, soW;
  for (run = 0; run < tam; run ++)
  {
    pedra = 0; posi = run; noW = posi; max = posi + 1;
    if (max == tam)
    { max = 0; }
    corA = colar[posi];
    soW = noW;
    if (corA == 'w')
    {
      while (colar[noW] == 'w')
      {
        noW --;
        if (noW < 0)
        {
          noW = tam - 1;
        }
        if (soW == noW)
        {
          break;
        }
      }
      corA = colar[noW];
      //printf("%c\n", corA);
    }
    while ((colar[posi] == corA || colar[posi] == 'w') && posi != max)
    {
      pedra ++;
      lim = posi;
      posi --;
      if (posi < 0)
      {
        posi = tam - 1;
      }
    }

    posi = run + 1; noW = posi; max = posi - 1;
    if (posi == tam)
    { posi = 0; noW = 0; max = tam - 1; }
    corB = colar[posi];
    soW = noW;
    if (corB == 'w')
    {
      while (colar[noW] == 'w')
      {
        noW ++;
        if (noW == tam)
        {
          noW = 0;
        }
        if (soW == noW)
        {
          break;
        }
      }
      corB = colar[noW];
    }
    while ((colar[posi] == corB || colar[posi] == 'w') && posi != max && posi != lim)
    {
      pedra ++;
      posi ++;
      if (posi == tam)
      { posi = 0; }
    }
    if (pedra > maior)
    {
      maior = pedra;
    }
  }
  printf("%d\n", maior);
  return(0);
}
