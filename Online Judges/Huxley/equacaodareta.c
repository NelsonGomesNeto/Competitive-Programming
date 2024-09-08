#include <stdio.h>

int main()
{
  int x1, y1, x2, y2;
  scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
  float a = (y2 - y1) * (-1);
  float b = (x2 - x1);
  float c = ((x1 * a) + (y1 * b)) * (-1);
  if (b != 0)
  {
    a /= b; c /= b; b /= b;
  }
  else
  {
    c /= a; a /= a;
  }
  printf("(%.2fx) + (%.2fy) + (%.2f) = 0\n", a, b, c);
  return(0);
}
