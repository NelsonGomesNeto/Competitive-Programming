#include <stdio.h>

struct item
{
  int valor, peso;
};

int max(int a, int b)
{
  return(a > b ? a : b);
}

int DP(int i, int resta, struct item ob[], int tam, int X, int m[][X])
{
  if (m[i][resta] != 1)
  {
    return(m[i][resta]);
  }
  if (i == tam)
  {
    m[i][resta] = 0;
  }
  else if (resta == 0)
  {
    m[i][resta] = 0;
  }
  else if (ob[i].peso > resta)
  {
    m[i][resta] = DP(i + 1, resta, ob, tam, resta, m);
  }
  else
  {
    m[i][resta] = max(ob[i].valor + DP(i + 1, resta - ob[i].peso, ob, tam, resta, m), DP(i + 1, resta, ob, tam, resta, m));
  }
  return(m[i][resta]);
  //printf("%d~%d\n", ob[i].valor, ob[i].peso);
}


int main()
{
  int itens, PesoMaxMochila;
  scanf("%d %d", &itens, &PesoMaxMochila);
  struct item obj[itens + 1];
  int ler, memo[itens][PesoMaxMochila];
  for (ler = 0; ler < itens; ler ++)
  {
    scanf("%d", &obj[ler].valor);
  }
  for (ler = 0; ler < itens; ler ++)
  {
    scanf("%d", &obj[ler].peso);
  }
  int o, b;
  for (o = 0; o < itens; o ++)
  {
    for (b = 0; b < PesoMaxMochila; b ++)
    {
      memo[o][b] = -1;
    }
  }
  DP(0, PesoMaxMochila, obj, itens, PesoMaxMochila, memo);
  for (o = 0; o < itens; o ++)
  {
    for (b = 0; b < PesoMaxMochila; b ++)
    {
      printf("%d\n", memo[o][b]);
    }
  }
  printf("%d\n", memo[0][PesoMaxMochila - 1]);
  return(0);
}
