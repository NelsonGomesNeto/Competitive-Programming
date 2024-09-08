#include <stdio.h>
#include <string.h>

int main()
{
  char nome[20]; scanf("%s", nome);
  char num[14]; int ler, R, G, B, posi = 0, tam, i;

  tam = strlen(nome);

  for (ler = 0; ler < 12; ler ++)
  {
    if (!(nome[ler] >= '0' && nome[ler] <= '9'
    || nome[ler] >= 'A' && nome[ler] <= 'F'))
    {
      nome[ler] = '0';
    }
  }

  while (tam % 3 != 0)
  {
    tam ++;
  }
  tam /= 3;

  for (ler = 0; ler < 12; ler ++)
  {
    if (nome[ler] >= '0' && nome[ler] <= '9'
    || nome[ler] >= 'A' && nome[ler] <= 'F')
    {
      num[ler] = nome[ler];
    }
    else
    {
      num[ler] = '0';
    }
  }
  char color[3][tam + 20];
  for (posi = 0, ler = 0; posi < 3; posi ++)
  {
    for (i = 0; i < tam; i ++, ler ++)
    {
      color[posi][i] = num[ler];
    }
  }
  color[0][2] = '\0';
  color[1][2] = '\0';
  color[2][2] = '\0';

  R = (int) strtol(color[0], 0, 16);
  G = (int) strtol(color[1], 0, 16);
  B = (int) strtol(color[2], 0, 16);
  printf("(%d,%d,%d)\n", R, G, B);
  return(0);
}
