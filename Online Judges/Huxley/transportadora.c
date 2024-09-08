#include <stdio.h>
#include <string.h>

struct caminhao
{
  long long int peso, atual, itens;
  long long int cargas[1000];
};

struct galpao
{
  long long int item;
};

int main()
{
  int caminhoes; int running = 0, run;
  scanf("%d", &caminhoes);
  do
  {
    run = 0;
    if (running > 0)
    {
      printf("\n");
    }
    running ++;
    struct caminhao c[caminhoes];
    struct galpao g[10000];
    int ler;
    for (ler = 0; ler < caminhoes; ler ++)
    {
      scanf("%Ld", &c[ler].peso);
      c[ler].atual = 0;
      c[ler].itens = 0;
    }
    char comando[10]; long long int num;
    int quanti = 0; long long int pesoAtual = 0;
    while (getchar() && scanf("%s", comando) != EOF && atoi(comando) <= 0 && comando[0] != '0')
    {
      scanf("%Ld", &num);
      if (strcmp(comando, "ADD") == 0)
      {
        g[quanti].item = num;
        pesoAtual += num;
        quanti ++;
        printf("%d %Ld\n", quanti, pesoAtual);
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
        if (pesoAtual < 0)
        {
          pesoAtual = 0;
        }
        quanti = arrasta;
        printf("%Ld %Ld\n", num, c[num].itens);
      }
      else if (strcmp(comando, "DEL") == 0)
      {
        c[num].itens --;
        if (c[num].itens < 0)
        {
          c[num].itens = 0;
        }
        c[num].atual -= c[num].cargas[c[num].itens];
        c[num].cargas[c[num].itens] = 0;
        printf("%Ld %Ld\n", num, c[num].itens);
      }
      else if (strcmp(comando, "INF") == 0)
      {
        printf("%Ld %Ld %Ld\n", num, c[num].itens, c[num].atual);
      }
    }
    if (atoi(comando) > 0 || comando[0] == '0')
    {
      run = 1;
    }
    else
    {
      run = 0;
    }
    caminhoes = atoi(comando);
  } while(run == 1);
  return(0);
}
