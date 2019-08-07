#include <stdio.h>

struct path
{
  int i, j;
};

int best;

void backtrack(int tam, int m[][tam], int i, int j, struct path p[], int custo, struct path bestP[])
{
  if (i == tam)
  {
    if (custo < best)
    {
      best = custo;
      for (i = 0; i < tam; i ++)
      {
        bestP[i].i = p[i].i;
        bestP[i].j = p[i].j;
      }
    }
    return;
  }
  if (i + 1 <= tam && j - 1 >= 0)
  {
    p[i].i = i; p[i].j = j;
    backtrack(tam, m, i + 1, j - 1, p, custo + m[i][j], bestP);
  }
  if (i + 1 <= tam) //Reto
  {
    p[i].i = i; p[i].j = j;
    backtrack(tam, m, i + 1, j, p, custo + m[i][j], bestP);
  }
  if (i + 1 <= tam && j + 1 < tam)
  {
    p[i].i = i; p[i].j = j;
    backtrack(tam, m, i + 1, j + 1, p, custo + m[i][j], bestP);
  }
}

int main()
{
  int tamanho; scanf("%d", &tamanho);
  int m[tamanho][tamanho], i, j;
  struct path p[tamanho];
  struct path bestPath[tamanho];
  for (i = 0; i < tamanho; i ++)
  {
    for (j = 0; j < tamanho; j ++)
    {
      scanf("%d", &m[i][j]);
      p[i].i = i;
      p[i].j = j;
    }
  }
  best = 999999;
  for (j = 0; j < tamanho; j ++)
  {
    backtrack(tamanho, m, 0, j, p, 0, bestPath);
  }
  printf("%d\n", best);
  for (i = tamanho - 1; i >= 0; i --)
  {
    printf("[%d,%d]", bestPath[i].i, bestPath[i].j);
    if (i != 0)
    {
      printf(" <- ");
    }
  } printf("\n");
  return(0);
}
