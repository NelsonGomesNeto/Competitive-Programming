#include <stdio.h>
#include <string.h>
#define DEBUG if(0)
#define nextI i + dy[k]
#define nextJ j + dx[k]

int best;
int dx[4] = {1, -1, 1, -1};
int dy[4] = {1, 1, -1, -1};

void printMatrix(int y, int x, int mat[][x])
{
  int i, j;
  for (i = 0; i < y; i ++)
  {
    for (j = 0; j < x; j ++)
      printf("%d ", mat[i][j]);
    printf("\n");
  }
}

void kill(int i, int j, int y, int x, int tab[][x], int killed)
{
  if (i < 0 || j < 0 || i >= y || j >= x) return;
  if (tab[i][j] != 0) return;

  if (killed > best) best = killed;

  int k;
  for (k = 0; k < 4; k ++)
  {
    if (!(nextI < 0 || nextI >= y || nextJ < 0 || nextJ >= x) && tab[nextI][nextJ] == 2)
    {
      tab[nextI][nextJ] = 8;
      kill(nextI + dy[k], nextJ + dx[k], y, x, tab, killed + 1);
      tab[nextI][nextJ] = 2;
    }
  }
}

int main()
{
  int y, x;
  while (scanf("%d %d", &y, &x) && !(y == 0 && x == 0))
  {
    int tab[y][x], i, j, k = 0;
    for (i = 0; i < y; i ++) memset(tab[i], 0, sizeof(tab[i]));

    for (i = y - 1; i >= 0; i --)
    {
      for (j = k; j < x; j += 2)
        scanf("%d", &tab[i][j]);
      k = 1 - k;
    }

    DEBUG printMatrix(y, x, tab);
    DEBUG printf("\n");

    best = 0;
    for (i = 0; i < y; i ++)
      for (j = 0; j < x; j ++)
        if (tab[i][j] == 1)
        {
          tab[i][j] = 0;
          kill(i, j, y, x, tab, 0);
          tab[i][j] = 1;
        }

    printf("%d\n", best);
  }

  return(0);
}