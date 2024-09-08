#include <stdio.h>
#include <string.h>

int main()
{
  int pedido[10010], quanti = 0, tira, tirando, foi = 0, run = 0; char oper;
  for (tirando = 0; tirando < 10010; tirando ++)
  {
    pedido[tirando] = 0;
  }
  while (scanf("%c", &oper) != EOF)
  {
    if (oper == 'a' || oper == 'A')
    {
      scanf("%d", &pedido[quanti]);
      quanti ++;
      run ++;
    }
    else if (oper == 'r' || oper == 'R')
    {
      foi = 0;
      scanf("%d", &tira);
      for (tirando = 0; tirando < run; tirando ++)
      {
        if (pedido[tirando] == tira)
        {
          pedido[tirando] = 0;
          printf("removido\n");
          foi ++;
        }
      }
      if (foi == 0)
      {
        printf("falha\n");
      }
      else
      {
        quanti --;
      }
    }
    else
    {
      foi = 0;
      for (tirando = 0; tirando < run; tirando ++)
      {
        if (foi == quanti - 1)
        {
          break;
        }
        if (pedido[tirando] != 0 && foi < quanti)
        {
          printf("%d ", pedido[tirando]);
          foi ++;
        }
      }
      if ((foi == 0 && tirando > 0) || quanti == 0)
      {
        printf("vazia\n");
      }
      else
      {
        while (tirando < run)
        {
          if (pedido[tirando] != 0)
          {
            printf("%d\n", pedido[tirando]);
          }
          tirando ++;
        }
      }
    }
    getchar();
  }
  return(0);
}
