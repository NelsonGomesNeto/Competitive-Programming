#include <stdio.h>
//NOT WORKING!!!
int main()
{
  int nVezes, ler, fecha, movements = 0;
  scanf("%d %d", &nVezes, &fecha);
  int pino[nVezes];
  for (ler = 0; ler < nVezes; ler ++)
  { scanf("%d", &pino[ler]); }

  while (pino[nVezes - 1] != fecha)
  {
    for (ler = 0; ler < nVezes; ler ++)
    {
      while (pino[ler] < fecha)
      {
        pino[ler] ++;
        pino[ler + 1] ++;
        movements ++;
      }
      while (pino[ler] > fecha)
      {
        pino[ler] --;
        pino[ler + 1] --;
        movements ++;
      }
    }
  }
  printf("%d\n", movements);
  return(0);
}
