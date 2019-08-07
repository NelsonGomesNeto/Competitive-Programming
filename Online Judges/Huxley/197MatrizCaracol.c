#include <stdio.h>
#include <string.h>
#define DEBUG if(0)
int inf = 999999;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void snail(int size, int mat[][size], int i, int j, int n)
{
  if (i < 0 || j < 0 || i >= size || j >= size) return;
  if (mat[i][j] != inf) return;
  DEBUG printf("%d %d\n", i, j);

  scanf("%d", &mat[i][j]);
  int k, cic;
  for (k = n, cic = 0; cic < 4; k ++, cic ++)
  {
    k %= 4;
    snail(size, mat, i + dy[k], j + dx[k], k);
  }
}

int main()
{
  int size; scanf("%d", &size);
  int mat[size][size], i, j;
  for (i = 0; i < size; i ++)
    for (j = 0; j < size; j ++)
      mat[i][j] = inf;

  snail(size, mat, 0, 0, 0);

  for (i = 0; i < size; i ++)
    for (j = 0; j < size; j ++)
      printf("%d\n", mat[i][j]);

  return(0);
}