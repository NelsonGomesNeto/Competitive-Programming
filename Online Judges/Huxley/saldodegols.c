#include <stdio.h>

int main()
{
  int jogos, run = 1;
  while (scanf("%d", &jogos) && jogos != 0)
  {
    if (run > 1)
    {
      printf("\n");
    }
    int saldo[jogos], a, b, ler;
    for (ler = 0; ler < jogos; ler ++)
    {
      scanf("%d %d", &a, &b);
      //printf("%d %d\n", a, b);
      saldo[ler] = a - b;
    }
    int Xi = 1, from = 1, Xf = 0, to = 0, atual = 0, melhor = -1;
    for (ler = 0; ler < jogos; ler ++)
    {
      to ++;
      atual += saldo[ler];
      if (atual < 0)
      {
        from = ler + 2;
        atual = 0;
      }
      else if (atual > 0)
      {
        if (atual > melhor || (atual == melhor && to - from >= Xf - Xi))
        {
          melhor = atual;
          Xi = from;
          Xf = to;
        }
      }
    }
    printf("Teste %d\n", run);
    if (melhor == -1)
    {
      printf("nenhum\n");
    }
    else
    {
      printf("%d %d\n", Xi, Xf);
    }
    run ++;
  }
  return(0);
}
