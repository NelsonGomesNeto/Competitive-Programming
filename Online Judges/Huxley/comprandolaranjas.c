#include <stdio.h>

int main()
{
  int laranjas; scanf("%i", &laranjas);
  int duzia; float preco = 0;
  duzia = laranjas / 12;
  preco += duzia * 8.35;
  if (laranjas % 12 > 0)
  {
    preco += (laranjas % 12) * (8.35 / 12);
  }
  printf("%i\n%.2f\n", duzia, preco);
  return(0);
}
