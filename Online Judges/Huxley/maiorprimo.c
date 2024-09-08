#include <stdio.h>

int main()
{
  int num, repeat, prim = 1;
  while (scanf("%i", &num) && num != 404)
  {
    for (repeat = 1; repeat < num; repeat ++)
    {
      if (num % repeat == 0 && repeat != 1)
      {
        repeat = num + 1;
        break;
      }
    }
    if (num >= prim && repeat == num)
    {
      prim = num;
    }
  }
  if (prim != 1)
  {
    printf("%i\n", prim);
  }
  else
  {
    printf("SEM PRIMOS\n");
  }
  return(0);
}
