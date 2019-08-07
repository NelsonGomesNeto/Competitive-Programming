#include <stdio.h>

int main()
{
  int H, W, full, aux; scanf("%d %d %d", &H, &W, &full); aux = W;
  int eX, eY, dX, dY; scanf("%d %d %d %d", &eX, &eY, &dX, &dY);
  while (H >= 0)
  {
    while (W >= 0)
    {
      if (H > eY || H < dY)
      {
        printf(".");
      }
      else
      {
        if (W < eX || W > dX)
        {
          printf(".");
        }
        else if (W == eX || W == dX || full == 1)
        {
          printf("*");
        }
        else
        {
          if (H != eY && H != dY)
          {
            printf(".");
          }
          else
          {
            printf("*");
          }
        }
      }
      W --;
    }
    printf("\n");
    W = aux;
    H --;
  }
  return(0);
}
