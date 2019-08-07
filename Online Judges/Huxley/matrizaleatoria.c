#include <stdio.h>
#define stop if (num > x * y) { break; }

int main()
{
  int y, x; scanf("%d %d", &y, &x);
  int matriz[y][x], j, i, deY = 0, ateY = y, deX = 1, ateX = x - 1, num = 1, tudo = x * y;
  while (num <= (y * x))
  {
    for (j = deY, i = deX - 1; j < ateY; j ++)
    {
      //printf("%d~%dx%d\n", num, j, i);
      matriz[j][i] = num;
      num ++;
    }
    stop
    for (j = ateY - 1, i = ateX; j >= deY; j --)
    {
      matriz[j][i] = num;
      num ++;
    }
    for (i = deX, j = ateY - 1; i < ateX; i ++)
    {
      matriz[j][i] = num;
      num ++;
    }
    for (i = deX, j = deY; i < ateX; i ++)
    {
      matriz[j][i] = num;
      num ++;
    }
    deY ++; ateY --; deX ++; ateX --;
  }

  for (j = 0; j < y; j ++)
  {
    for (i = 0; i < x - 1; i ++)
    {
      if (matriz[j][i] < 10)
      {
        printf("00%d ", matriz[j][i]);
      }
      else if (matriz[j][i] < 100)
      {
        printf("0%d ", matriz[j][i]);
      }
      else
      {
        printf("%d ", matriz[j][i]);
      }
    }
    if (matriz[j][i] < 10)
    {
      printf("00%d\n", matriz[j][i]);
    }
    else if (matriz[j][i] < 100)
    {
      printf("0%d\n", matriz[j][i]);
    }
    else
    {
      printf("%d\n", matriz[j][i]);
    }
  }
  return(0);
}
