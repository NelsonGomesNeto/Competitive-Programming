#include <stdio.h>

int main()
{
  int x1, y1, x2, y2, s, x3, y3;
  while (scanf("%d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &s, &x3, &y3) != EOF)
  {
    // printf("(%d, %d) (%d, %d) (%d, %d)\n", x1, y1, x2, y2, x3, y3);
    if (((x3 >= x1 && x3 <= x2) || (s && x3 >= x1) || (!s && x3 <= x2)))
      printf("S\n");
    else
      printf("N\n");
  } // y3 >= y1 && y3 <= y2 &&
  return(0);
}