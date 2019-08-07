#include <stdio.h>
#include <math.h>

int main()
{
  double x, y, yMax, yMin;
  while (scanf("%lf %lf", &x, &y) && !(x == 0 && y == 0))
  {
    yMax = 3 * x;
    yMin = x / 3;
    if (x > 0)
    {
      if (y <= yMax && y >= yMin)
        {
          printf("INTERIOR\n");
        }
        else
        {
          printf("EXTERIOR\n");
        }
    }
    else
    {
      if(y >= yMax && y <= yMin)
      {
        printf("INTERIOR\n");
      }
      else
      {
        printf("EXTERIOR\n");
      }
    }
  }
  return(0);
}

/*if (x >= 0)
{
  if (y <= yMax && y >= yMin)
  {
    printf("INTERIOR\n");
  }
  else
  {
    printf("EXTERIOR\n");
  }
}
else
{
  if (y >= yMax && y <= yMin)
  {
    printf("INTERIOR\n");
  }
  else
  {
    printf("EXTERIOR\n");
  }
}*/
