#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sleepcp(int milliseconds) // cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

int main()
{
  system("clear");
  int x, y, rX, rY, i, j, viva, gera, run, live; scanf("%d %d %d %d", &y, &x, &viva, &gera);
  int Xcel, Ycel; char matriz[x + 2][y + 2], aux[x + 2][y + 2];
  for (j = 0; j < y + 2; j ++)
  {
    for (i = 0; i < x + 2; i ++)
    {
      matriz[j][i] = ' ';
      aux[j][i] = ' ';
    }
  }
  for (run = 0; run < viva; run ++)
  {
    scanf("%d %d", &Xcel, &Ycel);
    matriz[Xcel + 1][Ycel + 1] = '@';
    aux[Xcel + 1][Ycel + 1] = '@';
  }
  for (run = 0; run < gera + 1; run ++)
  {
    for (j = 1; j < y + 1; j ++)
    {
      printf("      ");
      for (i = 1; i < x; i ++)
      {
        printf("%c", matriz[j][i]);
        live = 0;
        for (rY = j - 1; rY < j + 2; rY ++)
        {
          for (rX = i - 1; rX < i + 2; rX ++)
          {
            if (matriz[rY][rX] == '@' && !(rY == j && rX == i))
            {
              live ++;
            }
          }
        }
        if (matriz[j][i] == '@' && live < 2)
        {
          aux[j][i] = ' ';
        }
        else if (matriz[j][i] == '@' && live > 3)
        {
          aux[j][i] = ' ';
        }
        else if (matriz[j][i] == ' ' && live == 3)
        {
          aux[j][i] = '@';
        }
        else
        {
          aux[j][i] = matriz[j][i];
        }
      }
      printf("%c\n", matriz[j][i]);
      live = 0;
      for (rY = j - 1; rY < j + 2; rY ++)
      {
        for (rX = i - 1; rX < i + 2; rX ++)
        {
          if (matriz[rY][rX] == '@' && !(rY == j && rX == i))
          {
            live ++;
          }
        }
      }
      if (matriz[j][i] == '@' && live < 2)
      {
        aux[j][i] = ' ';
      }
      else if (matriz[j][i] == '@' && live > 3)
      {
        aux[j][i] = ' ';
      }
      else if (matriz[j][i] == ' ' && live == 3)
      {
        aux[j][i] = '@';
      }
      else
      {
        aux[j][i] = matriz[j][i];
      }
    }
    //sleepcp(25);
    system("clear");
    for (j = 1; j < y + 1; j ++)
    {
      for (i = 1; i < x + 1; i ++)
      {
        matriz[j][i] = aux[j][i];
      }
    }
  }
  return(0);
}
