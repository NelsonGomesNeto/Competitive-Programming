#include <stdio.h>

int search(int a[], int num, int xI, int xF)
{
  //printf("%d %d\n", xI, xF);
  if (num == a[(xF + xI) / 2] || xF - xI == 1)
  {
    return((xF + xI) / 2);
  }
  else if (num < a[(xF + xI) / 2])
  {
    search(a, num, xI, (xF + xI) / 2);
  }
  else
  {
    search(a, num, (xF + xI) / 2, xF);
  }
}

int main()
{
  int casas, ler, check; scanf("%d", &casas);
  int casaNum[casas];
  for (ler = 0; ler < casas; ler ++)
  {
    scanf("%d", &casaNum[ler]);
  }
  int escondido;
  scanf("%d", &escondido);
  for (ler = 0; ler < casas; ler ++)
  {
    //printf("%d\n", escondido - casaNum[ler]);
    int posi = search(casaNum, escondido - casaNum[ler], ler, casas);
    if (casaNum[ler] + casaNum[posi] == escondido)
    {
      printf("%d %d\n", casaNum[ler], casaNum[posi]);
      return(0);
    }
  }
}
