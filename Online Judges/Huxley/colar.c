#include <stdio.h>
#include <string.h>

int main()
{
  int tam, i, check, tudo, conta, fim = 0, next; scanf("%d", &tam);
  char string[tam + 10], corA, corB; scanf("%s", string);
  for (check = 0; check < tam; check ++)
  {
    tudo = 0; conta = 0;
    //printf("~~~~\n");
    for (i = check; tudo < tam; tudo ++, i ++)
    {
      i = i % tam;
      //printf("%d\n", i);
      next = i + 1;
      next = next % tam;
      if (tudo == 0)
      {
        while (string[next] == 'w')
        {
          next ++;
          next = next % tam;
        }
        corA = string[next];
        next = tam - 1 - i;
        while (string[next] == 'w')
        {
          next --;
          if (next < 0)
          {
            next += tam;
          }
        }
        corB = string[next];
      }
      if (corA == string[i] || string[i] == 'w')
      {
        if (corA != 'N')
        {
          conta ++;
        }
      }
      else
      {
        corA = 'N';
      }
      if (corB == string[tam - 1 - i] || string[tam - 1 - i] == 'w')
      {
        if (corB != 'N')
        {
          conta ++;
        }
      }
      else
      {
        corB = 'N';
      }
      if (conta > fim)
      {
        fim = conta;
      }
    }
      //printf("\n");
  }
  printf("\n%d\n", fim);
  return(0);
}
