#include <stdio.h>

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
    for (check = 0; check < casas; check ++)
    {
      if (casaNum[ler] + casaNum[check] == escondido)
      {
        printf("%d %d\n", casaNum[ler], casaNum[check]);
        return(0);
      }
    }
  }
}
