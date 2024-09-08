#include <stdio.h>

int tam;

int percorre(int field[][tam], int y, int x, int step)
{
  int mat[tam][tam], sub = 0, i, j;
  for (i = 0; i < tam; i ++)
  {
    for (j = 0; j < tam; j ++)
    {
      mat[i][j] = 0;
    }
  }
  while (step >= 0)
  {
    if (x + step < tam && y + sub < tam)
      mat[y + sub][x + step] = 1;
    if (x + step < tam && y - sub >= 0)
      mat[y - sub][x + step] = 1;

    if (x - step >= 0 && y + sub < tam)
      mat[y + sub][x - step] = 1;
    if (x - step >= 0 && y - sub >= 0)
      mat[y - sub][x - step] = 1;

    if (y + step < tam && x + sub < tam)
      mat[y + step][x + sub] = 1;
    if (y + step < tam && x - sub >= 0)
      mat[y + step][x - sub] = 1;

    if (y - step >= 0 && x + sub < tam)
      mat[y - step][x + sub] = 1;
    if (y - step >= 0 && x - sub >= 0)
      mat[y - step][x - sub] = 1;

    step --; sub ++;
  }
  for (i = 0; i < tam; i ++)
  {
    for (j = 0; j < tam; j ++)
    {
      field[i][j] += mat[i][j];
    }
  }
}

int printarMatriz(int mat[][tam])
{
  int i, j;
  for (i = 0; i < tam; i ++)
  {
    for (j = 0; j < tam; j ++)
    {
      printf("%d ", mat[i][j]);
    } printf("\n");
  } printf("\n");
}

int main()
{
  int dicas; scanf("%d %d", &tam, &dicas);
  int campo[tam][tam], y, x, dist;
  for (y = 0; y < tam; y ++)
  {
    for (x = 0; x < tam; x ++)
    {
      campo[y][x] = 0;
    }
  }
  while (dicas > 0)
  {
    scanf("%d %d %d", &x, &y, &dist);
    percorre(campo, y, x, dist);
    //printarMatriz(campo);
    dicas --;
  }
  int treasure = 0, bY, bX;
  for (y = 0; y < tam; y ++)
  {
    for (x = 0; x < tam; x ++)
    {
      if (campo[y][x] > treasure)
      {
        treasure = campo[y][x];
        bY = y; bX = x;
      }
    }
  }
  int notPossible = 0;
  for (y = 0; y < tam; y ++)
  {
    for (x = 0; x < tam; x ++)
    {
      if (campo[y][x] == treasure)
      {
        notPossible ++;
      }
    }
  }
  if (notPossible > 1)
  {
    printf("-1 -1\n");
  }
  else
  {
    printf("%d %d\n", bX, bY);
  }
  return(0);
}
