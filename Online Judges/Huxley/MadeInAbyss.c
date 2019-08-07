#include <stdio.h>
#include <string.h>

void swap(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}

void swapArray(int a[], int b[])
{
  int aux[10], i;
  for (i = 0; i < 10; i ++) aux[i] = a[i];
  for (i = 0; i < 10; i ++) a[i] = b[i];
  for (i = 0; i < 10; i ++) b[i] = aux[i];
}

void printPoints(int diggers, int mat[][10])
{
  int i, j;
  for (i = 0; i < diggers; i ++)
  {
    for (j = 0; j < 10; j ++)
      printf("%d ", mat[i][j]);
    printf("\n");
  }
}

int main()
{
  int diggers; scanf("%d", &diggers);
  int points[diggers][10], rank[diggers], level, i, j;
  for (i = 0; i < diggers; i ++)
  {
    rank[i] = i;
    scanf("%d", &level);
    memset(points[i], 0, sizeof(points[i]));
    int gold;
    for (j = 0; j < 10; j ++)
    {
      scanf("%d", &gold);
      if (j + 1 <= level)
        points[i][j] = gold;
    }
  }


  int o, b;
  for (o = 0; o < diggers; o ++)
  {
    for (b = o + 1; b < diggers; b ++)
    {
      int done = 0;
      for (i = 9; i >= 0; i --)
      {
        if (points[b][i] > points[o][i])
        {
          swap(&rank[b], &rank[o]);
          swapArray(points[b], points[o]);
          done = 1;
          break;
        }
        if (points[b][i] < points[o][i])
        {
          done = 1;
          break;
        }
      }
      if (done == 0)
        if ((b > o && rank[b] < rank[o]) || (b < o && rank[b] > rank[o]))
        {
          swap(&rank[b], &rank[o]);
          swapArray(points[b], points[o]);
        }
    }
  }

  for (i = 0; i < diggers; i ++)
    printf("%d\n", rank[i] + 1);

  return(0);
}