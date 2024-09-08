#include <stdio.h>
#include <string.h>

struct sprinklers
{
  int ID;
  long double temperatura;
  char fumaca;
};

int main()
{
  int testes, run; scanf("%d", &testes);
  for (run = 1; run <= testes; run ++)
  {
    int quantidade_sprinkler, ler, only = 0; long double temperatura_media = 0;
    scanf("%d", &quantidade_sprinkler);
    struct sprinklers s[quantidade_sprinkler + 10];
    for (ler = 0; ler < quantidade_sprinkler; ler ++)
    {
      scanf("%d %Lf %c", &s[ler].ID, &s[ler].temperatura, &s[ler].fumaca);
      temperatura_media += s[ler].temperatura;
    }
    temperatura_media = (long double) temperatura_media / (long double) quantidade_sprinkler;
    printf("TESTE %d\n", run);
    for (ler = 0; ler < quantidade_sprinkler; ler ++)
    {
      if (s[ler].temperatura >= 40 || toupper(s[ler].fumaca) == 'S' || s[ler].temperatura > temperatura_media * 1.15)
      {
        printf("%d\n", s[ler].ID);
      }
    }
  }
  return(0);
}
