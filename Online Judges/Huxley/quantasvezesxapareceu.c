#include <stdio.h>

int main()
{
  int x, num[10], repeat, xVezes = 0;
  for (repeat = 0; repeat < 10; repeat ++)
  {
    scanf("%i", &num[repeat]);
  }
  scanf("%i", &x);
  for (repeat = 0; repeat < 10; repeat ++)
  {
    if (x == num[repeat])
    {
      xVezes ++;
    }
  }
  printf("%i\n", xVezes);
  return(0);
}
