#include <stdio.h>
#include <math.h>

int main()
{
  float ax, ay, bx, by, cx, cy, BAx, BAy, BCx, BCy, angulo;
  scanf("%f %f", &ax, &ay);
  scanf("%f %f", &bx, &by);
  scanf("%f %f", &cx, &cy);
  BAx = ax - bx; BAy = ay - by;
  BCx = cx - bx; BCy = cy - by;
  angulo = ((BAx * BCx) + (BAy * BCy)) / ((sqrt(pow(BAx,2) + pow(BAy,2))) * (sqrt(pow(BCx,2) + pow(BCy,2))));
  angulo = acos(angulo) * 180 / acos(-1);
  printf("%.2f\n", angulo);
  angulo = acos(angulo/180);
}
