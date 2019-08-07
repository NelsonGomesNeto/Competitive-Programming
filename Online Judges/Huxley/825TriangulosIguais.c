#include <stdio.h>

int main()
{
  int t1x1, t1y1, t1x2, t1y2, t1x3, t1y3;
  scanf("%d %d %d %d %d %d", &t1x1, &t1y1, &t1x2, &t1y2, &t1x3, &t1y3);
  int t2x1, t2y1, t2x2, t2y2, t2x3, t2y3;
  scanf("%d %d %d %d %d %d", &t2x1, &t2y1, &t2x2, &t2y2, &t2x3, &t2y3);

  double t1d1 = (t1x2 - t1x1) * (t1x2 - t1x1) + (t1y2 - t1y1) * (t1y2 - t1y1), t1d2 = (t1x3 - t1x2) * (t1x3 - t1x2) + (t1y3 - t1y2) * (t1y3 - t1y2), t1d3 = (t1x1 - t1x3) * (t1x1 - t1x3) + (t1y1 - t1y3) * (t1y1 - t1y3);
  double t2d1 = (t2x2 - t2x1) * (t2x2 - t2x1) + (t2y2 - t2y1) * (t2y2 - t2y1), t2d2 = (t2x3 - t2x2) * (t2x3 - t2x2) + (t2y3 - t2y2) * (t2y3 - t2y2), t2d3 = (t2x1 - t2x3) * (t2x1 - t2x3) + (t2y1 - t2y3) * (t2y1 - t2y3);

  if ((t1d1 == t2d1 && t1d2 == t2d2 && t1d3 == t2d3) || (t1d1 == t2d2 && t1d2 == t2d1 && t1d3 == t2d3) || (t1d1 == t2d3 && t1d2 == t2d1 && t1d3 == t2d2) || (t1d1 == t2d1 && t1d2 == t2d3 && t1d3 == t2d2) || (t1d1 == t2d2 && t1d2 == t2d3 && t1d3 == t2d1) || (t1d1 == t2d3 && t1d2 == t2d2 && t1d3 == t2d1))
    printf("SIM\n");
  else
    printf("NAO\n");

  return(0);
}