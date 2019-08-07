#include <stdio.h>

int main()
{
  float x, y, z, media;
  scanf("%f\n%f\n%f", &x, &y, &z);
  media = (x + y + z) / 3;
  printf("A média entre %f, %f, %f é: %f\n", x, y, z, media);
  return(0);
}
