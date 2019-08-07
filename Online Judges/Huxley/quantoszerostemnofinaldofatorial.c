#include <stdio.h>

int main()
{
  int num, zero, repeat; scanf("%d", &num);
  /*for (repeat = 1; repeat < 200; repeat ++)
  {
    num += 1;
  }*/
  zero = num / 5;
  zero += num / 25;
  zero += num / 125;
  printf("%d\n", zero);
  return(0);
}
