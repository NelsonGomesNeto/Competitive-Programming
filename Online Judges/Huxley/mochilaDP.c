#include <stdio.h>

struct item
{
  int valor, peso;
};

int max(int a, int b)
{
  return(a > b ? a : b);
}

int DP(int i, int resta, struct item ob[], int tam)
{
  if (i == tam || resta <= 0)
  {
    return(0);
  }
  if (ob[i].peso > resta)
  {
    return(DP(i + 1, resta, ob, tam));
  }
  //printf("%d~%d\n", ob[i].valor, ob[i].peso);
  return(max(ob[i].valor + DP(i + 1, resta - ob[i].peso, ob, tam), DP(i + 1, resta, ob, tam)));
}


int main()
{
  int itens, PesoMaxMochila;
  scanf("%d %d", &itens, &PesoMaxMochila);
  struct item obj[itens + 1];
  int ler;
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
    for (b = o; b < itens; b ++)
    {
      if (obj[o].valor < obj[b].valor)
      {
        obj[itens] = obj[o];
        obj[o] = obj[b];
        obj[b] = obj[itens];
      }
    }
  }
  int melhor = DP(0, PesoMaxMochila, obj, itens);
  printf("%d\n", melhor);
  return(0);
}
