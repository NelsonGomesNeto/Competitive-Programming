#include <stdio.h>
#include <math.h>

int main()
{
  int testes, run; scanf("%d", &testes);
  for (run = 1; run <= testes; run ++)
  {
    int num, soma = 0, from, vezes, start; scanf("%d", &num);
    printf("caso %d:", run);
    from = pow(num,2) - num + 1;
    start = from;
    for (vezes = 0; vezes < num; from ++)
    {
      if (from % 2 != 0)
      {
        //soma += from;
        printf(" %d", from);
        vezes ++;
      }
    }
    /*while (soma != pow(num,3))
    {
    }*/
    printf("\n");
  }
}
