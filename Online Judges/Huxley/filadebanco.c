#include <stdio.h>

int main()
{
  int bancos, clientes; scanf("%d %d", &bancos, &clientes);
  int tempo[bancos], ler, entrada[clientes], antedimento[clientes], max, o, b, aux, limit = 0, inst = - 1;
  for (ler = 0; ler < bancos; ler ++)
  {
    tempo[ler] = 0;
  }
  for (ler = 0; ler < clientes; ler ++)
  {
    scanf("%d %d", &entrada[ler], &antedimento[ler]);
    //max = tempo[0] - entrada[ler];
    //tempo[0] += antedimento[ler];
    for (o = 0; o < bancos; o ++)
    {
      tempo[o] -= entrada[ler] - inst;
      if (tempo[o] < 0)
      {
        tempo[o] = 0;
      }
    }
    if (entrada[ler] > inst)
    {
      inst = entrada[ler];
    }
    for (o = 0; o < bancos; o ++)
    {
      for (b = o; b < bancos; b ++)
      {
        if (tempo[o] > tempo[b])
        {
          aux = tempo[o];
          tempo[o] = tempo[b];
          tempo[b] = aux;
        }
      }
    }
    if (tempo[0] > 20)
    {
      //printf("%d~%d\n", tempo[0], entrada[ler]);
      limit ++;
    }
    tempo[0] += antedimento[ler];
  }
  printf("%d\n", limit);
}
