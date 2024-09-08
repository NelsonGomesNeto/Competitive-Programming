#include <stdio.h>

void movement(int GoTo, int *x, int *y)
{
  if (GoTo == 1)
  {
    *x = *x + 1; *y = *y - 2;
  }
  else if (GoTo == 2)
  {
    *x = *x + 2; *y = *y - 1;
  }
  else if (GoTo == 3)
  {
    *x = *x + 2; *y = *y + 1;
  }
  else if (GoTo == 4)
  {
    *x = *x + 1; *y = *y + 2;
  }
  else if (GoTo == 5)
  {
    *x = *x - 1; *y = *y + 2;
  }
  else if (GoTo == 6)
  {
    *x = *x - 2; *y = *y + 1;
  }
  else if (GoTo == 7)
  {
    *x = *x - 2; *y = *y - 1;
  }
  else //GoTo == 8
  {
    *x = *x - 1; *y = *y - 2;
  }
}

int main()
{
  int matriz[8][8], i, j;
  for (j = 0; j < 8; j ++)
  {
    for (i = 0; i < 8; i ++)
    {
      if (j == 2 && i == 2)
      {
        matriz[j][i] = 1;
      }
      else if (j == 3 && i == 5)
      {
        matriz[j][i] = 1;
      }
      else if (j == 4 && i == 1)
      {
        matriz[j][i] = 1;
      }
      else if (j == 4 && i == 2)
      {
        matriz[j][i] = 1;
      }
      else
      {
        matriz[j][i] = 0;
      }
    }
  }
  int cavX = 4, cavY = 4, mov, act, run, stop = 0;
  scanf("%d", &mov);
  for (run = 1; run <= mov; run ++)
  {
    scanf("%d", &act);
    movement(act, &cavX, &cavY);
    //printf("%d~%d\n", cavX, cavY);
    if (matriz[cavY][cavX] == 1 && stop == 0)
    {
      stop = run;
    }
  }
  if (stop == 0)
  {
    stop = run - 1;
  }
  /*for (j = 0; j < 8; j ++)
  {
    for (i = 0; i < 8; i ++)
    {
      printf("%d ", matriz[j][i]);
    }
    printf("\n");
  }*/
  printf("%d\n", stop);
  return(0);
}
