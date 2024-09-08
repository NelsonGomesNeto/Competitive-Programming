#include <stdio.h>

int main()
{
  float x, y, z, media;
  scanf("%f\n%f\n%f", &x, &y, &z);
  media = (x + y + z) / 3;
  printf("O valor calculado foi: %f\n", media);
  return(0);
}
