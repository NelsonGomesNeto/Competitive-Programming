#include <stdio.h>

int main()
{
  int x, y; scanf("%d %d", &x, &y);
  if (x == 0 && y == 0)
  {
    printf("origem\n");
  }
  else if (x == 0)
  {
    printf("eixo y\n");
  }
  else if (y == 0)
  {
    printf("eixo x\n");
  }
  else if (x > 0 && y > 0)
  {
    printf("primeiro\n");
  }
  else if (x < 0 && y > 0)
  {
    printf("segundo\n");
  }
  else if (x < 0 & y < 0)
  {
    printf("terceiro\n");
  }
  else if (x > 0 && y < 0)
  {
    printf("quarto\n");
  }
  return(0);
}
