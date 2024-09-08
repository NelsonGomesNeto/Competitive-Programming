#include <stdio.h>

void printar(int vezes)
{
  printf("|");
  while (vezes > 0)
  {
    printf("*");
    vezes --;
  }
  printf("\n");
}

int main()
{
  int tam, ler, min = 0, limit = 1, maior = 0, posi, quanti[10]; scanf("%d", &tam);
  float num[tam];
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%f", &num[ler]);
  }
  for (ler = 0; ler < 10; ler ++)
  {
    quanti[ler] = 0;
  }
  for (limit = 1, min = 0, posi = 0; limit <= 10; posi ++, limit ++, min ++)
  {
    for (ler = 0; ler < tam; ler ++)
    {
      if (num[ler] > min && num[ler] <= limit)
      {
        quanti[posi] ++;
      }
      if (min == 0 && num[ler] == 0)
      {
        quanti[posi] ++;
      }
    }
    if (maior < quanti[posi])
    {
      maior = quanti[posi];
    }
  }
  printf("^\n");
  for (ler = 9; ler >= 0; ler --)
  {
    printar(quanti[ler]);
  }
  printf("+");
  for (ler = 0; ler < maior; ler ++)
  {
    printf("-");
  }
  printf(">\n");
  return(0);
}
