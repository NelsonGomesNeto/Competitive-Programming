#include <stdio.h>

int main()
{
  int X, Y, repeat;
  scanf("%i %i", &X, &Y);
  for (repeat = 1; repeat <= Y; repeat ++)
  {
    if (repeat % X != 0 && repeat != Y)
    {
      printf("%i ", repeat);
    }
    else
    {
      printf("%i\n", repeat);
    }
  }
  return(0);
}
