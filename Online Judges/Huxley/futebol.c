#include <stdio.h>

void swap(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}

int main()
{
  int jogos, gols;
  scanf("%d %d", &jogos, &gols);
  int saldo[jogos], ler;
  for (ler = 0; ler < jogos; ler ++)
  {
    int a, b;
    scanf("%d %d", &a, &b);
    saldo[ler] = a - b;
  }
  int o, b;
  for (o = 0; o < jogos; o ++)
  {
    for (b = o; b < jogos; b ++)
    {
      if (saldo[o] < saldo[b])
      {
        swap(&saldo[o], &saldo[b]);
      }
    }
  }
  for (o = 0; o < jogos; o ++)
  {
    if (gols <= 0)
    {
      o = jogos + 1;
      break;
    }
    if (saldo[o] <= 0)
    {
      saldo[o] ++;
      gols --;
      o --;
    }
  }
  int pontos = 0;
  for (o = 0; o < jogos; o ++)
  {
    if (saldo[o] > 0)
    {
      pontos += 3;
    }
    else if (saldo[o] == 0)
    {
      pontos ++;
    }
  }
  printf("%d\n", pontos);
  return(0);
}
