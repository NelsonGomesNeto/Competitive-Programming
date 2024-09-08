#include <stdio.h>

int main()
{
  int n, repeat;
  scanf("%i", &n);
  for (repeat = 1; repeat <= 9; repeat ++)
  {
    printf("%i X %i = %i\n", n, repeat, (n * repeat));
  }
  return(0);
}
