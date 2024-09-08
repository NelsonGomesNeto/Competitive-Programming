#include <stdio.h>
#include <string.h>

struct palavra
{
  char string[20]; int valor;
};

int main()
{
  int i, palavras, descricoes;
  scanf("%d %d", &palavras, &descricoes);
  struct palavra p[palavras];
  for (i = 0; i < palavras; i ++)
  {
    getchar();
    scanf("%s %d", p[i].string, &p[i].valor);
  }
  char texto[100];
  while (descricoes > 0)
  {
    long long int total = 0;
    while (scanf("%s", texto) && strcmp(texto, ".") != 0)
    {
      for (i = 0; i < palavras; i ++)
      {
        if (strcmp(texto, p[i].string) == 0)
        {
          total += p[i].valor;
          break;
        }
      }
    }
    printf("%lld\n", total);
    descricoes --;
  }
  return(0);
}
