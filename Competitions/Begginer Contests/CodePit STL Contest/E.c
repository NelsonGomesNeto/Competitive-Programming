#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct letras
{
  char letra; long long cent;
};

int main()
{
  int tests; scanf("%d", &tests);
  while (tests > 0)
  {
    int paid; scanf("%d", &paid);
    struct letras l[paid + 10]; int ler;
    for (ler = 0; ler < paid; ler ++)
    {
      getchar();
      scanf("%c %lld", &l[ler].letra, &l[ler].cent);
    }
    long long cents = 0;
    long long dolar = 0;
    int linhas; scanf("%d", &linhas);
    char let;
    getchar();
    while (linhas > 0)
    {
      while (scanf("%c", &let) && let != '\n')
      {
        for (ler = 0; ler < paid; ler ++)
        {
          if (let == l[ler].letra)
          {
            cents += l[ler].cent;
            if (cents >= 100)
            {
              dolar += (long long int) cents / 100;
              cents %= 100;
            }
          }
        }
      }
      linhas --;
    }
    printf("%lld.%.2lld$\n", dolar, cents);
    tests --;
  }
  return(0);
}
