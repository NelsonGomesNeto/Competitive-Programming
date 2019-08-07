#include <stdio.h>

void printArray(int size, int a[][size])
{
  int i, j, c = 0;
  for (i = 0; i < 1; i ++)
  {
    //c = 0;
    for (j = 0; j < size; j ++)
      printf("%d ", a[i][j]);
    printf("\n");
  }
  printf("\n");
}

int main()
{
  int size;
  while (scanf("%d", &size) != EOF)
  {
    int a[size][size][size], i, j, t;
    for (i = 0; i < size; i ++)
    for (j = 0; j < size; j ++)
    for (t = 0; t < size; t ++)
    a[i][j][t] = 0;

    for (i = 0; i < size; i ++)
    a[0][i][i] = 1;
    //scanf("%d", &a[0][i][i]);

    int k = 1;
    for (i = 0; i < size - 1; i ++)
    {
      for (j = 0; j < size - 1 - i; j ++, k *= -1)
      {
        if (k == 1)
        {
          for (t = 0; t < size; t ++)
          {
            a[i + 1][j][t] += a[i][j][t] + a[i][j + 1][t];
          }
        }
        else
        {
          for (t = 0; t < size; t ++)
          {
            a[i + 1][j][t] += a[i][j][t] - a[i][j + 1][t];
          }
        }
      }
    }
    printArray(size, a[i]);
  }
}
