#include <stdio.h>

int main()
{
  int Y, X; scanf("%d %d", &Y, &X);
  int mat[Y][X], i, j;
  for (i = 0; i < Y; i ++)
  {
    for (j = 0; j < X; j ++)
    {
      scanf("%d", &mat[i][j]);
    }
  }
  int ans = 1;
  for (i = 0; i < Y; i ++)
  {
    int first = 0, zeroDe, d, k;
    for (j = 0; j < X; j ++)
    {
      if (mat[i][j] != 0 && first == 0)
      {
        first = 1;
        zeroDe = j;
        for (d = i + 1; d < Y; d ++)
        {
          for (k = zeroDe; k >= 0; k --)
          if (mat[d][k] != 0)
          {
            ans = 0;
          }
        }
      }
    }
    if (first == 0)
    {
      for (d = i + 1; d < Y; d ++)
      {
        for (k = 0; k < X; k ++)
        {
          if (mat[d][k] != 0)
          {
            ans = 0;
          }
        }
      }
    }
  }
  if (ans == 0)
  {
    printf("N");
  }
  else
  {
    printf("S");
  }
  return(0);
}
