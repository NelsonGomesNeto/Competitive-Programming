#include <stdio.h>

int main()
{
  int n, nBack, i = 0, iCar, onceI = 1, j = 0, jCar, onceJ = 0;
  scanf("%i", &n);
  int matriz[n][n];
  iCar = n - 1;
  jCar = n - 1;
  n *= n;
  nBack = n;
  while (n > 0)
  {
    scanf("%i", &matriz[i][j]);
    printf("%i %i\n", i, j);
    if (j < jCar && )
    {
      j ++;
    }
    else
    {
      if (i < iCar)
      {
        i ++;
      }
      else
      {
        if (j > 0)
        {
          if (onceJ == 0)
          {

            onceI --;
            onceJ ++;
          }
          j --;
        }
        else
        {
          if (onceI == 0)
          {
            iCar = iCar - i;
            onceJ --;
            onceI ++;
          }
          i --;
        }
      }
    }
    n --;
  }
  n = nBack;
  i = 0; j = 0;
  while (n > 0)
  {
    printf("%i\n", matriz[i][j]);
    i ++;
    n --;
  }
  return(0);
}
