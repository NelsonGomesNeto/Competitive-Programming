#include <stdio.h>

int main()
{
  int redes; scanf("%d", &redes);
  int area[220][220], Xi, Xf, Yi, Yf, j, i, total = 0;
  for (j = 0; j < 220; j ++)
  {
    for (i = 0; i < 220; i ++)
    {
      area[j][i] = 0;
    }
  }
  while (redes > 0)
  {
    scanf("%d %d %d %d", &Xi, &Xf, &Yi, &Yf);
    for (j = Yi + 100; j < Yf + 100; j ++)
    {
      for (i = Xi + 100; i < Xf + 100; i ++)
      {
        area[j][i] = 1;
      }
    }
    redes --;
  }
  for (j = 0; j < 220; j ++)
  {
    for (i = 0; i < 220; i ++)
    {
      if (area[j][i] == 1)
      {
        total ++;
      }
    }
  }
  printf("%d\n", total);
  return(0);
}
