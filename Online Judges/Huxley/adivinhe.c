#include <stdio.h>
#include <string.h>

int desiste(char sequencia[999999], int length)
{
  int checkDesiste;
  for (checkDesiste = 0; checkDesiste < length; checkDesiste ++)
  {
    if (sequencia[checkDesiste] != '0')
    {
      return(1);
    }
  }
  return(0);
}

int main()
{
  int jogos; scanf("%d", &jogos);
  while (jogos > 0)
  {
    int tamanho; scanf("%d", &tamanho);
    int certo = 0, miss = 0, check, checkMiss; char base[tamanho], baseTemp[tamanho], try[tamanho];
    getchar(); scanf("%[^\n]", base);
    try[0] = '1';
    while (!(certo == tamanho && miss == 0) && desiste(try, tamanho) == 1)
    {
      strcpy(baseTemp,base);
      certo = 0; miss = 0;
      getchar(); scanf("%[^\n]", try);
      for (check = 0; check < tamanho; check ++)
      {
        if (baseTemp[check] == try[check])
        {
          baseTemp[check] = '8';
          try[check] = '9';
          certo ++;
        }
      }
      for (check = 0; check < tamanho; check ++)
      {
        //printf("~~~~~~~~~\n");
        for (checkMiss = 0; checkMiss < tamanho; checkMiss ++)
        {
          if (baseTemp[check] == try[checkMiss] && check != checkMiss)
          {
            miss ++;
            baseTemp[check] = '8';
            try[checkMiss] = '9';
          }
          //printf("%c~~%c~~%d\n", baseTemp[check], try[checkMiss], miss);
        }
      }
      if (desiste(try,tamanho) == 1)
      {
        printf("(%d,%d)\n", certo, miss);
      }
    }
    jogos --;
  }
  //printf("Fim\n");
  return(0);
}
