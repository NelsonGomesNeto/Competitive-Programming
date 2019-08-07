#include <stdio.h>
#include <string.h>

struct pessoa
{
  char nome[999], cor[999], tam;
};

int main()
{
  int quanti, i, run = 0;
  while (scanf("%d", &quanti) && quanti != 0)
  {
    if (run > 0)
    {
      printf("\n");
    }
    run ++;
    struct pessoa p[quanti];
    for (i = 0; i < quanti; i ++)
    {
      getchar();
      scanf("%[^\n]", p[i].nome);
      getchar();
      scanf("%s", p[i].cor);
      getchar();
      scanf("%c", &p[i].tam);
    }
    int o, b; char aux[99999], unik;
    for (o = 0; o < quanti; o ++)
    {
      for (b = o; b < quanti; b ++)
      {
        if (strcmp(p[o].cor, p[b].cor) > 0)
        {
          strcpy(aux, p[o].cor);
          strcpy(p[o].cor, p[b].cor);
          strcpy(p[b].cor, aux);

          strcpy(aux, p[o].nome);
          strcpy(p[o].nome, p[b].nome);
          strcpy(p[b].nome, aux);

          unik = p[o].tam;
          p[o].tam = p[b].tam;
          p[b].tam = unik;
        }
        else if (strcmp(p[o].cor, p[b].cor) == 0)
        {
          if (p[o].tam < p[b].tam)
          {
            strcpy(aux, p[o].cor);
            strcpy(p[o].cor, p[b].cor);
            strcpy(p[b].cor, aux);

            strcpy(aux, p[o].nome);
            strcpy(p[o].nome, p[b].nome);
            strcpy(p[b].nome, aux);

            unik = p[o].tam;
            p[o].tam = p[b].tam;
            p[b].tam = unik;
          }
          else if (p[o].tam == p[b].tam)
          {
            if (strcmp(p[o].nome, p[b].nome) > 0)
            {
              strcpy(aux, p[o].cor);
              strcpy(p[o].cor, p[b].cor);
              strcpy(p[b].cor, aux);

              strcpy(aux, p[o].nome);
              strcpy(p[o].nome, p[b].nome);
              strcpy(p[b].nome, aux);

              unik = p[o].tam;
              p[o].tam = p[b].tam;
              p[b].tam = unik;
            }
          }
        }
      }
    }
    for (i = 0; i < quanti; i ++)
    {
      printf("%s %c %s\n", p[i].cor, p[i].tam, p[i].nome);
    }
  }
  return(0);
}
