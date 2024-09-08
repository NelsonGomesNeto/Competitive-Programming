#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define swap \
  c[cartas] = c[b];\
  c[b] = c[o];\
  c[o] = c[cartas];\

struct carta
{
  int dia, mes, ano;
  char month[100], remetente[100], destinatario[100];
};

int getNum(char m[])
{
  int i;
  for (i = 0; m[i] != '\0'; i ++)
  {
    m[i] = tolower(m[i]);
  }
  if (strcmp(m, "janeiro") == 0)
  {
    return(1);
  }
  if (strcmp(m, "fevereiro") == 0)
  {
    return(2);
  }
  /*if (strcmp(m, "março") == 0)
  {
    return(3);
  }*/
  if (strcmp(m, "abril") == 0)
  {
    return(4);
  }
  if (strcmp(m, "maio") == 0)
  {
    return(5);
  }
  if (strcmp(m, "junho") == 0)
  {
    return(6);
  }
  if (strcmp(m, "julho") == 0)
  {
    return(7);
  }
  if (strcmp(m, "agosto") == 0)
  {
    return(8);
  }
  if (strcmp(m, "setembro") == 0)
  {
    return(9);
  }
  if (strcmp(m, "outubro") == 0)
  {
    return(10);
  }
  if (strcmp(m, "novembro") == 0)
  {
    return(11);
  }
  if (strcmp(m, "dezembro") == 0)
  {
    return(12);
  }
  //Se for março
  return(3);
}

int main()
{
  int cartas; scanf("%d", &cartas);
  struct carta c[cartas + 1];
  int ler;
  for (ler = 0; ler < cartas; ler ++)
  {
    scanf("%d de %s de %d\n", &c[ler].dia, c[ler].month, &c[ler].ano);
    char aux[100];
    strcpy(aux, c[ler].month);
    c[ler].mes = getNum(aux);
    scanf("%[^\n]", c[ler].remetente);
    getchar();
    scanf("%[^\n]", c[ler].destinatario);
  }
  int o, b;
  for (o = 0; o < cartas; o ++)
  {
    for (b = o; b < cartas; b ++)
    {
      if (c[b].ano < c[o].ano)
      {
        swap
      }
      else if (c[b].ano == c[o].ano)
      {
        if (c[b].mes < c[o].mes)
        {
          swap
        }
        else if (c[b].mes == c[o].mes)
        {
          if (c[b].dia < c[o].dia)
          {
            swap
          }
          else if (c[b].dia == c[o].dia)
          {
            if (strcmp(c[b].remetente, c[o].remetente) < 0)
            {
              swap
            }
            else if (strcmp(c[b].remetente, c[o].remetente) == 0)
            {
              if (strcmp(c[b].destinatario, c[o].destinatario) < 0)
              {
                swap
              }
            }
          }
        }
      }
    }
  }
  for (ler = 0; ler < cartas; ler ++)
  {
    printf("%d de %s de %d\n", c[ler].dia, c[ler].month, c[ler].ano);
    printf("%s\n", c[ler].remetente);
    printf("%s\n", c[ler].destinatario);
  }
  return(0);
}
