#include <stdio.h>

int main()
{
  int quanti; scanf("%d", &quanti);
  int acoes[quanti], ler, menor[quanti], maior[quanti], melhor;
  for (ler = 0; ler < quanti; ler ++)
  {
    scanf("%d", &acoes[ler]);
    if (ler == 0 || menor[ler - 1] > acoes[ler])
    {
      menor[ler] = acoes[ler];
    }
    else
    {
      menor[ler] = menor[ler - 1];
    }
  }
  for (ler = quanti - 1; ler >= 0; ler --)
  {
    if (ler == quanti - 1 || maior[ler + 1] < acoes[ler])
    {
      maior[ler] = acoes[ler];
    }
    else
    {
      maior[ler] = maior[ler + 1];
    }
  }

  for (ler = 0; ler < quanti; ler ++)
  {
    if (ler == 0 || maior[ler] - menor[ler] > melhor)
    {
      melhor = maior[ler] - menor[ler];
    }
  }
  printf("%d\n", melhor);
  return(0);
}
