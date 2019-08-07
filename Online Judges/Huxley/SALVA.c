#include <stdio.h>

struct caminhao
{
  long int peso, atual, itens;
  long int cargas[1000];
};

struct galpao
{
  long int item;
};

int main()
{
  int caminhoes; scanf("%d", &caminhoes);
  struct caminhao c[caminhoes];
  struct galpao g[1000];
  int ler;
  for (ler = 0; ler < caminhoes; ler ++)
  {
    scanf("%ld", &c[ler].peso);
    c[ler].atual = 0;
    c[ler].itens = 0;
  }
  char comando[10]; long int num;
  int quanti = 0; long int pesoAtual;
  while (getchar() && scanf("%s", comando) != EOF)
  {
    scanf("%ld", &num);
    if (strcmp(comando, "ADD") == 0)
    {
      g[quanti].item = num;
      pesoAtual += num;
      quanti ++;
      printf("%d %ld\n", quanti, pesoAtual);
    }
    else if (strcmp(comando, "LOA") == 0)
    {
      int enche = 0;
      while (c[num].atual + g[enche].item <= c[num].peso && enche < quanti)
      {
        c[num].atual += g[enche].item;
        pesoAtual -= g[enche].item;
        c[num].cargas[c[num].itens] = g[enche].item;
        c[num].itens ++;
        enche ++;
      }
      int arrasta;
      for (arrasta = 0; enche < quanti; arrasta ++, enche ++)
      {
        g[arrasta].item = g[enche].item;
      }
      quanti = arrasta;
      printf("%ld %ld\n", num, c[num].itens);
    }
    else if (strcmp(comando, "DEL") == 0)
    {
      c[num].itens --;
      c[num].atual -= c[num].cargas[c[num].itens];
      c[num].cargas[c[num].itens] = 0;
      printf("%ld %ld\n", num, c[num].itens);
    }
    else if (strcmp(comando, "INF") == 0)
    {
      printf("%ld %ld %ld\n", num, c[num].itens, c[num].atual);
    }
  }
  return(0);
}
