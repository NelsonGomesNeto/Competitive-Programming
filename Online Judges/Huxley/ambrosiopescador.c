#include <stdio.h>
#include <math.h>

#define Y1 (y3 >= y1 && y3 <= y1)
#define Y2 (y3 >= y2 && y3 <= y1)

int main()
{
  double x1, y1, x2, y2, S, x3, y3, aux, m, a, b, c, dist;
  scanf("%lf %lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &S, &x3, &y3);
  double det;

  m = (y2 - y1) / (x2 - x1);
  b = -1;
  a = m;
  c = (m * (-x1)) + y1;
  dist = ((x3 * a) + (y3 * b) + c) / sqrt(pow(a,2) + pow(b,2));

  /*if (x2 >= x1 && y2 >= y1)
  {
    det = 1/2 * ((x1 * y2) + (y1 * x3) + (x2 * y3)) - ((x2 * y1) + (x1 * y3) + (x3 * y2));
  }
  else
  {
    aux = x1;
    x1 = x2;
    x2 = aux;
    aux = y1;
    y1 = y2;
    y2 = aux;
    det = 1/2 * ((x1 * y2) + (y1 * x3) + (x2 * y3)) - ((x2 * y1) + (x1 * y3) + (x3 * y2)) * -1;
  }*/

  //printf("%lf\n", dist);
  if (S == 0)
  {
    if ((x1 != x2 && y1 == y2 && y3 > y1) || (y1 != y2 && x1 == x2 && x3 > x2) || (x1 != x2 && y1 != y2 && dist > 0) || (x1 == x2 && y1 == y2 &&))
    {
      printf("N\n");
    }
    else
    {
      printf("S\n");
    }
  }
  else
  {
    if ((x1 == x2 && y1 == y2))
    {
      printf("S\n");
      return(0);
    }
    if ((x1 != x2 && y1 == y2 && y3 > y1) || (y1 != y2 && x1 == x2 && x3 < x2) || (x1 != x2 && y1 != y2 && dist < 0))
    {
      printf("N\n");
    }
    else
    {
      printf("S\n");
    }
  }
  return(0);
}
/* x1 y1 1
   x2 y2 1
   x3 y3 1
   1 1 5 5 0 2 3 = S
   1 1 1 1 0 1 0 = N*/
