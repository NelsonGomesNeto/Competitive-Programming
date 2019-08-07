#include <stdio.h>

int corrigir(int posicao, int casa)
{
  while(posicao >= casa || posicao < 0)
  {
    if (posicao >= casa)
    {
      posicao -= casa;
    }
    else if (posicao < 0)
    {
      posicao += casa;
    }
  }
  return(posicao);
}

int main()
{
  int casas, jogadores, rodadas, lertabu, lerroda, roda, fim;
  scanf("%d %d %d", &casas, &jogadores, &rodadas);
  int tabuleiro[casas + 10], posi[jogadores + 10];
  for (lertabu = 0; lertabu < casas; lertabu ++)
  {
    scanf("%d", &tabuleiro[lertabu]);
  }
  for (fim = 0; fim < jogadores; fim ++)
  {
    posi[fim] = 0;
  }
  for (lerroda = 0; lerroda < rodadas; lerroda ++)
  {
    for (fim = 0; fim < jogadores; fim ++)
    {
      scanf("%d", &roda);
      posi[fim] += roda;
      posi[fim] = corrigir(posi[fim],casas);
      posi[fim] += tabuleiro[posi[fim]];
      posi[fim] = corrigir(posi[fim],casas);
    }
  }
  for (fim = 0; fim < jogadores; fim ++)
  {
    printf("%d\n", posi[fim]);
  }
  return(0);
}
