#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
  int testes; scanf("%d", &testes);
  while (testes > 0)
  {
    int numeros; scanf("%d", &numeros);
    long long int num[numeros + 10]; int ler;
    for (ler = 0; ler < numeros; ler ++)
    {
      scanf("%Ld", &num[ler]);
    }
    long long int raz = (num[1] - num[0]), from = 1, aux = 1, to = 1, auxTo = 1, quanti = 0, prev = 0;
    for (ler = 0; ler < numeros - 1; ler ++)
    {
      //printf("%Ld ~~ %Ld\n", raz, quanti);
      if (raz != (num[ler + 1] - num[ler]))
      {
        raz = (num[ler + 1] - num[ler]);
        if (quanti > prev)
        {
          prev = quanti;
          to = auxTo;
          auxTo = ler + 1;
          from = aux;
        }
        aux = ler + 1;
        quanti = 0;
        ler --;
      }
      else
      {
        quanti ++;
        auxTo ++;
      }
    }
    if (raz == num[ler] - num[ler - 1])
    {
      if (quanti > prev)
      {
        prev = quanti;
        to = auxTo;
        from = aux;
      }
    }
    //printf("%Ld ~~ %Ld / %lf\n", raz, prev, (double)abs(num[ler] - num[ler - 1]));
    printf("%Ld %Ld\n", from, to);
    testes --;
  }
  return(0);
}
