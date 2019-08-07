#include <stdio.h>
#include <string.h>

int main()
{
  int testes; scanf("%d", &testes);
  while (testes > 0)
  {
    int avali, ler, soma, check; scanf("%d", &avali);
    soma = 0;
    for (ler = 0; ler < avali; ler ++)
    {
      char word[9999]; scanf("%s", word);
      for (check = 0; check < strlen(word); check ++)
      {
        soma += ((int) word[check] - 65) + ler + check;
      }
    }
    printf("%d\n", soma);
    testes --;
  }
  return(0);
}
