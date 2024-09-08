#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}

int main()
{
  int genes, reversas, run = 0;
  while (scanf("%d", &genes) && genes != 0)
  {
    int genome[genes], ler;
    for (ler = 0; ler < genes; ler ++)
    {
      genome[ler] = ler + 1;
    }
    scanf("%d", &reversas);
    int Xi[reversas], Xf[reversas];
    for (ler = 0; ler < reversas; ler ++)
    {
      scanf("%d %d", &Xi[ler], &Xf[ler]);
      Xi[ler] --; Xf[ler] --;
    }
    for (ler = reversas - 1; ler >= 0; ler --)
    {
      for (; Xi[ler] < Xf[ler]; Xi[ler] ++, Xf[ler] --)
      {
        swap(&genome[Xi[ler]], &genome[Xf[ler]]);
      }
    }
    int consultas, c; scanf("%d", &consultas);
    run ++;
    printf("Genome %d\n", run);
    for (ler = 0; ler < consultas; ler ++)
    {
      scanf("%d", &c);
      printf("%d\n", genome[c - 1]);
    }
  }
  return(0);
}
