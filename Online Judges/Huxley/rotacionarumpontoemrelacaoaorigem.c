#include <stdio.h>
#include <math.h>

int main()
{
  int x, y; double rotacao, xR, yR;
  while (scanf("%d %d %lf", &x, &y, &rotacao) != EOF)
  {
    rotacao = (rotacao * acos(-1)) / 180;
    xR = (x * cos(rotacao)) - (y * sin(rotacao));
    yR = (x * sin(rotacao)) + (y * cos(rotacao));
    printf("%.2lf %.2lf\n", xR, yR);
  }
  return(0);
}
