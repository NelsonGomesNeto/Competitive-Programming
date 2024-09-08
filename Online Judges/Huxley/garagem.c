#include <stdio.h>

int main()
{
  int L, C, H, l, c, h;
  scanf("%i %i %i %i %i %i", &L, &C, &H, &l, &c, &h);
  if ((l <= L) && (c <= C) && (h <= H))
  {
    printf("SIM\n");
  }
  else
  {
    printf("NAO\n");
  }
  return(0);
}
