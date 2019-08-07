#include <stdio.h>

int main()
{
  int pedras, sapos, ler, pulo, posi;
  scanf("%d %d", &pedras, &sapos);
  int temounao[pedras + 999];
  for (ler = 0; ler < pedras; ler ++)
  {
    temounao[ler] = 0;
  }
  for (ler = 0; ler < sapos; ler ++)
  {
    scanf("%d %d", &posi, &pulo);
    temounao[posi - 1] = 1;
    if (pulo > 0)
    {
      while (posi < pedras)
      {
        temounao[(posi - 1) + pulo] = 1;
        posi += pulo;
      }
      while (posi > 0)
      {
        if (pulo >= 0)
        {
          temounao[(posi - 1) - pulo] = 1;
        }
        posi -= pulo;
      }
    }
  }
  for (ler = 0; ler < pedras; ler ++)
  {
    printf("%d\n", temounao[ler]);
  }
  return(0);
}
