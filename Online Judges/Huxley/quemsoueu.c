#include <stdio.h>

int main()
{
  int testes, run = 1; scanf("%d", &testes);
  while (run <= testes)
  {
    int comandos; scanf("%d", &comandos);
    long int fila[comandos], pilha[comandos];
    int ler, f = 0, p = 0, eFila = 1, ePilha = 1;
    for (ler = 0; ler < comandos; ler ++)
    {
      int oper; long int num;
      scanf("%d %ld", &oper, &num);
      if (oper == 1)
      {
        fila[f] = num;
        fila[f + 1] = 0;
        pilha[p] = num;
        p ++; f ++;
      }
      else if (oper == 2)
      {
        p --;
        if (pilha[p] != num)
        {
          ePilha = 0;
        }
        pilha[p] = 0;
        if (fila[0] != num)
        {
          eFila = 0;
        }
        fila[0] = 0;
        int shift;
        for (shift = 0; shift < f; shift ++)
        {
          fila[shift] = fila[shift + 1];
        }
        f --;
      }
    }
    printf("caso %d: ", run);
    if (eFila == ePilha)
    {
      if (eFila == 1)
      {
        printf("ambas\n");
      }
      else
      {
        printf("nenhuma\n");
      }
    }
    else if (eFila > ePilha)
    {
      printf("fila\n");
    }
    else
    {
      printf("pilha\n");
    }
    run ++;
  }
  return(0);
}
