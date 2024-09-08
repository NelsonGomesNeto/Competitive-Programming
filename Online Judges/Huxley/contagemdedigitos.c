#include <stdio.h>

int main()
{
  int menor, maior, conta, aux, vezes[10];
  while (scanf("%d %d", &menor, &maior) && !(menor == 0 && maior == 0))
  {
    for (conta = 0; conta < 10; conta ++)
    {
      vezes[conta] = 0;
    }
    while (menor <= maior)
    {
      for (conta = 0; conta <= 9; conta ++)
      {
        aux = menor;
        while (aux > 0)
        {
          //printf("%d~~%d\n", aux % 10, aux);
          if (aux % 10 == conta)
          {
            vezes[conta] ++;
          }
          aux /= 10;
        }
      }
      menor ++;
    }
    for (conta = 0; conta < 9; conta ++)
    {
      printf("%d ", vezes[conta]);
    }
    printf("%d\n", vezes[conta]);
  }
  return(0);
}
