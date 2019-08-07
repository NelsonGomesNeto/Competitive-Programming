#include <stdio.h>

int main()
{
  int x, y, j, i, escada = 0, zero = 0, last = 0, no = 0, stop = 0; scanf("%d %d", &x, &y);
  int matriz[x + 10][y + 10];
  for (j = 0; j < x; j ++)
  {
    for (i = 0; i < y; i ++)
    {
      scanf("%d", &matriz[j][i]);
    }
  }
  for (j = 0; j < x; j ++)
  {
    no = 0; stop = 0;
    for (i = 0; i < y; i ++)
    {
      if (matriz[j][i] == 0 && stop == 0)
      {
        no ++;
        for (last = i; last >= 0; last --)
        {
          for (zero = j + 1; zero < x; zero ++)
          {
            if (matriz[zero][last] != 0)
            {
              printf("N");
              return(0);
            }
          }
        }
      }
      if (matriz[j][i] != 0)
      {
        no = 0; stop ++;
        for (last = i; last >= 0; last --)
        {
          for (zero = j + 1; zero < x; zero ++)
          {
            if (matriz[zero][last] != 0)
            {
              printf("N");
              return(0);
            }
          }
        }
        i = y;
      }
    }
    if (no == y - 1 && x > 1 && y > 1)
    {
      for (zero = j; zero < x; zero ++)
      {
        for (last = i; zero < y; last ++)
        {
          if (matriz[last][zero] != 0)
          {
            printf("N");
            return(0);
          }
        }
      }
    }
    //printf("%d\n", matriz[i][j]);
  }
  printf("S");
  return(0);
}
