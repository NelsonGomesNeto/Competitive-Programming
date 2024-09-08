#include <stdio.h>

int main()
{
  int X, Y;
  scanf("%i %i", &X, &Y);
  if ((X >= 0 && X <= 432) && (Y >= 0 && Y <= 468))
  {
    printf("dentro\n");
  }
  else
  {
    printf("fora\n");
  }
  return(0);
}
