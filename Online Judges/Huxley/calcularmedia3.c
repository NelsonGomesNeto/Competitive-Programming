#include <stdio.h>

int main()
{
  float x, y, media;
  scanf("%f\n%f", &x, &y);
  media = (x + y) / 2;
  printf("A média entre %f, %f, é: %f\n", x, y, media);
  return(0);
}
