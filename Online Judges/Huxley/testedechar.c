#include <stdio.h>

int main()
{
  int repeat;
  for (repeat = 0; repeat < 256; repeat ++)
  {
    printf("%d ~ %c\n", (char) repeat, repeat);
  }
  return(0);
}
