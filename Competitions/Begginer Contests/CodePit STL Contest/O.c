#include <stdio.h>
#include <string.h>
#define change swap(&p[o].ano, &p[b].ano, &p[o].mes, &p[b].mes, &p[o].dia, &p[b].dia);
#define troca change swapC(p[o].nome, p[b].nome);
struct pessoa
{
  char nome[999];
  int dia, mes, ano;
};

void swap(int *a, int *b, int *c, int *d, int *e, int *f)
{
  int aux;
  aux = *a;
  *a = *b;
  *b = aux;
  aux = *c;
  *c = *d;
  *d = aux;
  aux = *e;
  *e = *f;
  *f = aux;
}
void swapC(char s[], char g[])
{
  char auxC[999];
  strcpy(auxC, s);
  strcpy(s, g);
  strcpy(g, auxC);
}
int main()
{
  int pessoas; scanf("%d", &pessoas);
  struct pessoa p[pessoas]; int ler;
  for (ler = 0; ler < pessoas; ler ++)
  {
    getchar();
    scanf("%s %d %d %d", p[ler].nome, &p[ler].dia, &p[ler].mes, &p[ler].ano);
  }
  int o, b;
  for (o = 0; o < pessoas; o ++)
  {
    for (b = o; b < pessoas; b ++)
    {
      if (p[o].ano >= p[b].ano)
      {
        if (p[o].ano == p[b].ano)
        {
          if (p[o].mes >= p[b].mes)
          {
            if (p[o].mes == p[b].mes)
            {
              if (p[o].dia > p[b].dia)
              {
                troca
              }
            }
            else
            {
              troca
            }
          }
        }
        else
        {
          troca
        }
      }
    }
  }
  int i;
  for (i = 0; i < pessoas; i ++)
  {
    printf("%s\n", p[i].nome);
  }
  return(0);
}
