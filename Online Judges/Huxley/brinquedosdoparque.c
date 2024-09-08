#include <stdio.h>

int main()
{
  int altura, idade, brinquedos = 0;
  scanf("%i %i", &altura, &idade);
  if (altura >= 150 && idade >= 12)
  {
    brinquedos ++;
  }
  if (altura >= 140 && idade >= 14)
  {
    brinquedos ++;
  }
  if (altura >= 170 || idade >= 16)
  {
    brinquedos ++;
  }
  printf("%i\n", brinquedos);
  return(0);
}
