#include <stdio.h>

int main()
{
  int Konsultas, xCen, yCen, x, y, repeat;
  while (scanf("%i", &Konsultas) && Konsultas != 0)
  {
    scanf("%i %i", &xCen, &yCen);
    for (repeat = 0; repeat < Konsultas; repeat ++)
    {
      scanf("%i %i", &x, &y);
      if (x == xCen || y == yCen)
      {
        printf("divisa\n");
      }
      else if (x > xCen && y > yCen)
      {
        printf("NE\n");
      }
      else if (x > xCen && y < yCen)
      {
        printf("SE\n");
      }
      else if (x < xCen && y > yCen)
      {
        printf("NO\n");
      }
      else
      {
        printf("SO\n");
      }
    }
  }
  return(0);
}
