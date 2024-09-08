#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap p[quanti] = p[o]; \
p[o] = p[b]; \
p[b] = p[quanti] \

#define newCountry strcpy(c[quanti].pais, string); \
c[quanti].ouro = 0; \
c[quanti].prata = 0; \
c[quanti].bronze = 0; \

struct country
{
  char pais[50];
  int ouro, prata, bronze;
};

void ordenar(struct country p[], int quanti)
{
  int o, b;
  for (o = 0; o < quanti; o ++)
  {
    for (b = o; b < quanti; b ++)
    {
      if (p[b].ouro > p[o].ouro)
      { swap; }
      else if (p[b].ouro == p[o].ouro)
      {
        if (p[b].prata > p[o].prata)
        { swap; }
        else if (p[b].prata == p[o].prata)
        {
          if (p[b].bronze > p[o].bronze)
          { swap; }
        }
      }
    }
  }
}

int main()
{
  char string[50], medalha[50]; int i, j, quanti = 0, willAt = 0;
  struct country c[999];
  while (scanf("%c", &string[0]) && string[0] != '*')
  {
    i = 1;
    while (scanf("%c", &string[i]) && string[i] != ',')
    {
      i ++;
    } string[i] = '\0';
    if (quanti == 0)
    {
      newCountry;
      willAt = 0; quanti ++;
    }
    else
    {
      int achou = 0;
      for (j = 0; j < quanti; j ++)
      {
        if (strcmp(c[j].pais, string) == 0)
        {
          willAt = j; achou ++;
        }
      }
      if (achou == 0)
      {
        willAt = j;
        newCountry;
        quanti ++;
      }
    }
    scanf("%s", medalha); getchar();
    if (strcmp(medalha, "ouro") == 0)
      (c[willAt].ouro) ++;
    if (strcmp(medalha, "prata") == 0)
      (c[willAt].prata) ++;
    if (strcmp(medalha, "bronze") == 0)
      (c[willAt].bronze) ++;
  }
  ordenar(c, quanti);
  for (j = 0; j < quanti; j ++)
    printf("%d)%s ouro:%d prata:%d bronze:%d\n", j + 1, c[j].pais, c[j].ouro, c[j].prata, c[j].bronze);
  return(0);
}
