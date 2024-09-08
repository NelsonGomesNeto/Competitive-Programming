#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>

char sol[50];
int fim = 0;

int feito(int x[][4])
{
  int i, j, conta = 1;
  for (i = 0; i < 4; i ++)
  {
    for (j = 0; j < 4; j ++)
    {
      if (x[i][j] != conta && !(i == 3 && j == 3))
      {
        return(1);
      }
      conta ++;
    }
  }
  return(0);
}

void swap(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}

char bestSol[50];
int tam;

void find(int g[][4], int y, int x, int i)
{
  if (i == 24 || i > tam)
  {
    return;
  }
  if (feito(g) == 0)
  //if (sol[0] == 'L')
  {
    //printf("%s\n", sol);
    fim = 1;
    if (bestSol[0] == '1' || strlen(sol) < strlen(bestSol))
    {
      strcpy(bestSol, sol);
      tam = strlen(bestSol);
    }
    /*int iM, j;
    for (iM = 0; iM < 4; iM ++)
    {
      for (j = 0; j < 4; j ++)
      {
        printf("%d ", g[iM][j]);
      } printf("\n");
    }*/
    return;
  }
  if (y - 1 >= 0 && ((i > 0 && sol[i - 1] != 'D') || i == 0))
  {
    swap(&g[y][x], &g[y - 1][x]);
    sol[i] = 'U';
    find(g, y - 1, x, i + 1);
    sol[i] = '\0';
    swap(&g[y][x], &g[y - 1][x]);
  }
  if (y + 1 < 4 && ((i > 0 && sol[i - 1] != 'U') || i == 0))
  {
    swap(&g[y][x], &g[y + 1][x]);
    sol[i] = 'D';
    find(g, y + 1, x, i + 1);
    sol[i] = '\0';
    swap(&g[y][x], &g[y + 1][x]);
  }
  if (x + 1 < 4 && ((i > 0 && sol[i - 1] != 'L') || i == 0))
  {
    swap(&g[y][x], &g[y][x + 1]);
    sol[i] = 'R';
    find(g, y, x + 1, i + 1);
    sol[i] = '\0';
    swap(&g[y][x], &g[y][x + 1]);
  }
  if (x - 1 >= 0 && ((i > 0 && sol[i - 1] != 'R') || i == 0))
  {
    swap(&g[y][x], &g[y][x - 1]);
    sol[i] = 'L';
    find(g, y, x - 1, i + 1);
    sol[i] = '\0';
    swap(&g[y][x], &g[y][x - 1]);
  }
}

int main()
{
  int tests, x, y; scanf("%d", &tests);
  while (tests > 0)
  {
    int m[4][4], i, j;
    for (i = 0; i < 4; i ++)
    {
      for (j = 0; j < 4; j ++)
      {
        scanf("%d", &m[i][j]);
        if (m[i][j] == 0)
        {
          y = i;
          x = j;
        }
      }
    }
    fim = 0; bestSol[0] = '1'; bestSol[1] = '\0';
    tam = 50;
    find(m, y, x, 0);
    if (fim == 0)
    {
      printf("This puzzle is not solvable.\n");
    }
    else
    {
      printf("%s\n", bestSol);
    }
    tests --;
  }
  return(0);
}
