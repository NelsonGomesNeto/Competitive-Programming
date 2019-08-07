#include <stdio.h>

int main()
{
  int Y, X, rotate;
  scanf("%d %d %d", &Y, &X, &rotate);
  int j, i, square[Y][X];
  for (j = 0; j < Y; j ++)
  {
    for (i = 0; i < X; i ++)
    {
      scanf("%d", &square[j][i]);
    }
  }
  rotate %= 4;
  if (rotate == 0)
  {
    for (j = 0; j < Y; j ++)
    {
      for (i = 0; i < X - 1; i ++)
      {
        printf("%d ", square[j][i]);
      } printf("%d\n", square[j][i]);
    }
  }
  else if (rotate == 1 || rotate == -3)
  {
    for (i = 0; i < X; i ++)
    {
      for (j = Y - 1; j > 0; j --)
      {
        printf("%d ", square[j][i]);
      } printf("%d\n", square[j][i]);
    }
  }
  else if (rotate == 2 || rotate == -2)
  {
    for (j = Y - 1; j >= 0; j --)
    {
      for (i = X - 1; i > 0; i --)
      {
        printf("%d ", square[j][i]);
      } printf("%d\n", square[j][i]);
    }
  }
  else if (rotate == 3 || rotate == -1)
  {
    for (i = X - 1; i >= 0; i --)
    {
      for (j = 0; j < Y - 1; j ++)
      {
        printf("%d ", square[j][i]);
      } printf("%d\n", square[j][i]);
    }
  }
  return(0);
}
