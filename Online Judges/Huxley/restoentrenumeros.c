#include <stdio.h>

int main()
{
  int X, Y, aux; scanf("%d\n%d", &X, &Y);
  if (Y < X)
  {
    aux = X;
    X = Y;
    Y = aux;
  }
  while (X < Y)
  {
    if (X % 5 == 2 || X % 5 == 3)
    {
      printf("%d\n", X);
    }
    X ++;
  }
  return(0);
}
