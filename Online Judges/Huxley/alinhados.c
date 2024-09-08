#include <stdio.h>

struct pendrive
{
  double x, y;
};

int main()
{
  int pendrives;
  while (scanf("%d", &pendrives) && pendrives != 0)
  {
    int ler, alinhado = 1, up = 0, right = 0;
    double slope; struct pendrive p[pendrives];
    for (ler = 0; ler < pendrives; ler ++)
    {
      scanf("%lf %lf", &p[ler].x, &p[ler].y);
      if (ler == 1)
      {
        if (p[1].x - p[0].x == 0)
        {
          up = 1;
        }
        else if (p[1].y - p[0].y == 0)
        {
          right = 1;
        }
        else
        {
          slope = (p[1].x - p[0].x) / (p[1].y - p[0].y);
        }
      }
      else if (ler > 1)
      {
        if ((up == 1 && p[ler].x - p[ler - 1].x != 0)
        || (right == 1 && p[ler].y - p[ler - 1].y != 0)
        || (right != 1 && up != 1 && slope != (p[ler].x - p[ler - 1].x) / (p[ler].y - p[ler - 1].y)))
        {
          alinhado = 0;
        }
      }
    }
    if (alinhado == 0)
    {
      printf("NAO_ALINHADOS\n");
    }
    else
    {
      printf("ALINHADOS\n");
    }
  }
  return(0);
}
