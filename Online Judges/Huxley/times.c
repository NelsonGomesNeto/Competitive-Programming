#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct jogador jogador; //Como é definido e como eu quero chamar

struct jogador
{
  char nome[52]; int hab;
};

int compareHabilities(const void *c, const void *d)
{
  const jogador *a = c, *b = d;
  if (a->hab > b->hab)
    return(-1);
  return(1);
}

int compareNomes(const void *c, const void *d)
{
  const char *a = c, *b = d;
  if (strcmp(a, b) < 0)
    return(-1);
  return(1);
}


int main()
{
  //Lê as coisas
  int jogadores, times; scanf("%d %d", &jogadores, &times);
  jogador j[jogadores + 1]; int i;
  int divDeJogadores = (int) ceil((double) jogadores / times);
  char party[times][divDeJogadores][52];
  int *quanti = calloc(times, sizeof(int));
  for (i = 0; i < jogadores; i ++)
  {
    getchar();
    scanf("%s %d", j[i].nome, &j[i].hab);
  }
  //Ordena os jogadores
  qsort(j, jogadores, sizeof(jogador), compareHabilities);
  /*int o, b;
  for (o = 0; o < jogadores; o ++)
  {
    for (b = o + 1; b < jogadores; b ++)
    {
      if (j[b].hab > j[o].hab)
      {
        j[jogadores] = j[b];
        j[b] = j[o];
        j[o] = j[jogadores];
      }
    }
  }
  */
  //Separa os times
  int k;
  for (i = 0, k = 0; i < jogadores; i ++, k ++)
  {
    k %= times;
    strcpy(party[k][quanti[k]], j[i].nome);
    quanti[k] += 1;
  }
  //Ordenação de nomes
  for (i = 0; i < times; i ++)
    qsort(party[i], quanti[i], sizeof(party[i][0]), compareNomes);
  /*for (i = 0; i < times; i ++)
  {
    for (o = 0; o < quanti[i]; o ++)
    {
      for (b = o + 1; b < quanti[i]; b ++)
      {
        if (strcmp(party[i][b], party[i][o]) < 0)
        {
          char aux[52];
          strcpy(aux, party[i][b]);
          strcpy(party[i][b], party[i][o]);
          strcpy(party[i][o], aux);
        }
      }
    }
  }
  */
  //Printa os times
  for (i = 0; i < times; i ++)
  {
    printf("Time %d\n", i + 1);
    for (k = 0; k < quanti[i]; k ++)
    {
      printf("%s\n", party[i][k]);
    } printf("\n");
  }
  free(quanti);
  return(0);
}
