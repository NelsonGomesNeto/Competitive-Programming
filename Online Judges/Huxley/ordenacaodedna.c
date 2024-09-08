#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int tam;

struct dna
{
  char na[51]; int ord, origi;
};

int evaluate(char string[])
{
  int o, b, desordem = 0; char aux;
  for (o = 0; o < tam; o ++)
  {
    for (b = o; b < tam; b ++)
    {
      if (string[o] > string[b])
      {
        desordem ++;
      }
    }
  }
  return(desordem);
}

int main()
{
  int testes; scanf("%d", &testes);
  while (testes > 0)
  {
    int quanti, i; scanf("%d %d", &tam, &quanti);
    struct dna d[quanti + 1]; char auxS[51];
    for (i = 0; i < quanti; i ++)
    {
      getchar();
      scanf("%s", d[i].na);
      strcpy(auxS, d[i].na);
      d[i].ord = evaluate(auxS);
      //printf("%d\n", d[i].ord);
      d[i].origi = i;
    }
    int o, b;
    for (o = 0; o < quanti; o ++)
    {
      for (b = o; b < quanti; b ++)
      {
        if (d[o].ord > d[b].ord || (d[o].ord == d[b].ord && d[o].origi > d[b].origi))
        {
          d[quanti] = d[o];
          d[o] = d[b];
          d[b] = d[quanti];
        }
      }
    }
    for (i = 0; i < quanti; i ++)
    {
      printf("%s\n", d[i].na);
    }
    printf("\n");
    testes --;
  }
  return(0);
}
