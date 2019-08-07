#include <stdio.h>

int main()
{
  int x, y, j, i, escada = 0, zero = 0, last = 0, no = 0; scanf("%d %d", &x, &y);
  int matriz[x + 10][y + 10];
  for (j = 0; j < x; j ++)
  {
    for (i = 0; i < y; i ++)
    {
      scanf("%d", &matriz[i][j]);
    }
  }
  for (j = 0; j < x; j ++)
  {
    for (i = 0; i < y; i ++)
    {
      if (matriz[i][j] == 0)
      {
        for (zero = j; zero < x; zero ++)
        {
          if (matriz[i][zero] != 0)
          {
            printf("N");
            return(0);
          }
        }
      }
      else
      {
        no ++;
      }
    }
    //printf("%d\n", matriz[i][j]);
  }
  if (no != x * y)
  {
    printf("S");
  }
  else
  {
    printf("N");
  }
  return(0);
}
