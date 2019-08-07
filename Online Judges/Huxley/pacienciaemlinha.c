#include <stdio.h>

struct carta
{
  int classe; char naipe;
};
int quanti[52];

void puxa(struct carta ca[52][52], int de)
{
  while (quanti[de + 1] > 0)
  {
    ca[de][quanti[de + 1] - 1] = ca[de + 1][quanti[de + 1] - 1];
    quanti[de + 1] --; quanti[de] ++;
  }
}

void organiza(struct carta c[52][52], int from)
{
  int i;
  for (i = from; i < 51; i ++)
  {
    if (quanti[i] == 0)
    {
      puxa(c, i);
    }
  }
}

int change;

int pile(struct carta c[52][52], int pos, int i)
{
  while (quanti[i - (pos)] > 0 && quanti[i] > 0 && (c[i][quanti[i] - 1].classe == c[i - (pos)][quanti[i - (pos)] - 1].classe
  ||  c[i][quanti[i] - 1].naipe == c[i - (pos)][quanti[i - (pos)] - 1].naipe))
  {
    c[i - (pos)][quanti[i - (pos)]] = c[i][quanti[i] - 1];
    quanti[i - (pos)] ++; quanti[i] --;
    change = 1;
    if (quanti[i] == 0)
    {
      organiza(c, i); return(1);
    }
    i -= (pos);
    if (i - (pos) < 0)
    {
      return(0);
    }
  }
  return(0);
}

void play(struct carta ca[52][52], int left) //left starts with 51
{
  int i, soma = 0;
  change = 0;
  for (i = 0; i < 52; i ++)
  {
    if (quanti[i] == 0) { printf("~~%d\n", soma); break; }
    printf("%d ", quanti[i]);
    soma += quanti[i];
    //printf("%d%c ", ca[i][0].classe, ca[i][0].naipe);
  } printf("\n");
  for (i = 0; i <= left; i ++)
  {
    if (i - (3) >= 0 && quanti[i - (3)] > 0 && quanti[i] > 0)
    {
      left -= pile(ca, 3, i);
    }
    if (i - (1) >= 0 && quanti[i - (1)] > 0 && quanti[i] > 0)
    {
      left -= pile(ca, 1, i);
    }
    if (change == 1)
    {
      play(ca, left);
    }
  }
}

void putClass(char valor, struct carta *ca)
{
  if (valor == 'A')
  {
    (*ca).classe = 0; return;
  }
  if (valor <= '9')
  {
    (*ca).classe = 1; return;
  }
  if (valor == 'T')
  {
    (*ca).classe = 2; return;
  }
  if (valor == 'J')
  {
    (*ca).classe = 3; return;
  }
  if (valor == 'Q')
  {
    (*ca).classe = 4; return;
  }
  (*ca).classe = 5; return;
}

int main()
{
  char card, naip; int i;
  struct carta c[52][52];
  while (scanf("%c", &card) && card != '#')
  {
    scanf("%c", &c[0][0].naipe);
    putClass(card, &c[0][0]); quanti[0] = 1;
    for (i = 1; i < 52; i ++)
    {
      getchar();
      scanf("%c%c", &card, &c[i][0].naipe);
      putClass(card, &c[i][0]); quanti[i] = 1;
    }
    play(c, 51); int soma = 0;
    for (i = 0; i < 52; i ++)
    {
      if (quanti[i] == 0) { printf("~~%d\n", soma); break; }
      printf("%d ", quanti[i]);
      soma += quanti[i];
      //printf("%d%c ", ca[i][0].classe, ca[i][0].naipe);
    } printf("\n");
    for (i = 0; i < 52; i ++)
    {
      printf("%d%c ", c[i][0].classe, c[i][0].naipe);
    } printf("\n");
    getchar();
  }
  return(0);
}
