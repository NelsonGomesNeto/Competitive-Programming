#include <stdio.h>

int main()
{
  int repeat, n[101];
  for (repeat = 0; repeat < 101; repeat ++)
  {
    scanf("%d", &n[repeat]);
  }
  for (repeat = 0; repeat < 100; repeat ++)
  {
    if (n[100] == n[repeat])
    {
      printf("%d\n", repeat);
    }
  }
  return(0);
}
