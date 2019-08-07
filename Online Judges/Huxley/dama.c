#include <stdio.h>

int main()
{
  int x1, y1, x2, y2, modX, modY;
  while (scanf("%i %i %i %i", &x1, &y1, &x2, &y2)
      && x1 != 0 && y1 != 0 && x2 != 0 && y2 != 0)
  {
    modX = (x1 - x2); modY = (y1 - y2);
    if (modX < 0)
    {
      modX *= (-1);
    }
    if (modY < 0)
    {
      modY *= (-1);
    }
    if (x1 == x2 && y1 == y2)
    {
      printf("0\n");
    }
    else if ((x1 == x2 || y1 == y2)
            || modX == modY)
    {
      printf("1\n");
    }
    else
    {
      printf("2\n");
    }
  }
  return(0);
}
