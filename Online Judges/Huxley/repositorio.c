#include <stdio.h>
#include <stdlib.h>

struct programa
{
  int id, versao;
};

int main()
{
  int pc, internet, i; scanf("%d %d", &pc, &internet);
  struct programa p[pc + internet + 1];
  struct programa install[pc + internet + 1];
  int *ins = calloc((pc + internet + 1), sizeof(int));
  int aux = pc + internet + 1, atual = 0;
  for (i = 0; i < pc; i ++)
  {
    scanf("%d %d", &p[i].id, &p[i].versao);
  }
  int id, versao, j, did;
  for (i = 0; i < internet; i ++)
  {
    scanf("%d %d", &id, &versao);
    did = 0;
    for (j = 0; j < pc; j ++)
    {
      if (p[j].id == id)
      {
        did = 1;
        if (p[j].versao < versao)
        {
          p[j].versao = versao;
          ins[j] = 1;
          break;
        }
      }
    }
    if (did == 0)
    {
      p[pc].id = id; p[pc].versao = versao;
      ins[pc] = 1;
      pc ++;
    }
  }
  for (i = 0; i < pc; i ++)
  {
    if (ins[i] == 1)
    {
      install[atual] = p[i];
      atual ++;
    }
  }
  int o, b;
  for (o = 0; o < atual; o ++)
  {
    for (b = o; b < atual; b ++)
    {
      if (install[o].id > install[b].id)
      {
        install[aux] = install[o];
        install[o] = install[b];
        install[b] = install[aux];
      }
    }
  }
  for (o = 0; o < atual; o ++)
  {
    printf("%d %d\n", install[o].id, install[o].versao);
  }
  return(0);
}
