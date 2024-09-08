#include <stdio.h>
#include <string.h>

int musicos, bestLevel; char best[4], atual[4], copy[4];

void save(int lev)
{
  int o, b; char aux;
  strcpy(copy, atual);
  for (o = 0; o < 3;  o ++)
  {
    for (b = o; b < 3; b ++)
    {
      if (copy[o] > copy[b])
      {
        aux = copy[o];
        copy[o] = copy[b];
        copy[b] = aux;
      }
    }
  }
  if (lev == bestLevel)
  {
    if (strcmp(copy, best) > 0)
    {
      return;
    }
  }
  int i;
  for (i = 0; i < 3; i ++)
  {
    best[i] = copy[i];
  }
}

void bt(int ent[][musicos], int i, int qM, int level)
{
  if (qM == 3)
  {
    if (level >= bestLevel)
    {
      save(level);
      bestLevel = level;
    }
    return;
  }
  if (i == musicos)
  {
    return;
  }
  int j;
  for (j = 0; j < musicos; j ++)
  {
    if (j != i)
    {
      atual[qM] = j + 1;
      bt(ent, i + 1, qM + 1, level + ent[i][j]);
      bt(ent, i + 1, qM, level);
    }
  }
}

int main()
{
  int pares, i, j;
  while (scanf("%d %d", &musicos, &pares) && !(musicos == 0 && pares == 0))
  {
    int entro[musicos][musicos];
    for (i = 0; i < musicos; i ++)
    {
      for (j = 0; j < musicos; j ++)
      {
        entro[i][j] = 0;
      }
    }
    int a, b, niv;
    for (i = 0; i < pares; i ++)
    {
      scanf("%d %d %d", &a, &b, &niv);
      entro[a - 1][b - 1] = niv;
    }
    bestLevel = 0;
    bt(entro, 0, 0, 0);
    for (i = 0; i < 2; i ++)
    {
      printf("%d ", best[i]);
    } printf("%d\n", best[i]);
  }
  return(0);
}
