#include <stdio.h>

void check(int jogo[], int i, int m, int dif, int *times)
{
  int face, j, atual = 0;
  if (i == m)
  {
    for (j = 0; j < m; j ++)
    {
      if (jogo[j] == 1)
      {
        atual ++;
      }
      else
      {
        atual --;
      }
    }
    if (atual == dif || atual == dif * - 1)
    {
      (*times) ++;
    }
    return;
  }
  for (face = 0; face < 2; face ++)
  {
    jogo[i] = face;
    check(jogo, i + 1, m, dif, &*times);
  }
}

int main()
{
  int moedas, diferenca;
  scanf("%d %d", &moedas, &diferenca);
  int game[moedas], vezes = 0;
  check(game, 0, moedas, diferenca, &vezes);
  printf("%d\n", vezes);
  return(0);
}
