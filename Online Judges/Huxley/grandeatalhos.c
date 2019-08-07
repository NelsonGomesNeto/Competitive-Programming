#include <stdio.h>
#include <string.h>

int main()
{
  int testes, atalhos, ler, change, troca, foi;
  scanf("%d", &testes);
  while (testes > 0)
  {
    char base[9999], fim[9999];
    getchar(); scanf("%[^\n]", base);
    scanf("%d", &atalhos);
    char atabase[atalhos + 10], atatroca[atalhos + 10][999];
    for (ler = 0; ler < atalhos; ler ++)
    {
      getchar();
      scanf("%c", &atabase[ler]);
      getchar();
      scanf("%[^\n]", atatroca[ler]);
    }
    for (ler = 0; ler < strlen(base); ler ++)
    {
      foi = 0;
      if (base[ler] == '*')
      {
        ler ++;
        for (change = 0; change < atalhos; change ++)
        {
          if (base[ler] == atabase[change])
          {
            foi ++;
            printf("%s", atatroca[change]);
          }
        }
        if (foi == 0)
        {
          ler --;
        }
      }
      if (foi == 0 || base[ler] == '*')
      {
        printf("%c", base[ler]);
      }
    }
    printf("\n");
    testes --;
  }
  return(0);
}
